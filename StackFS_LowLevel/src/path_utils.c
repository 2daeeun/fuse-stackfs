#include "../include/path_utils.h"
#include "../include/hash_table.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* Function which generates the hash depending on the ino number
 * and full path */
size_t name_hash(struct lo_data *lo_data, fuse_ino_t ino,
                 const char *fullpath) {
  uint64_t hash = ino;
  uint64_t oldhash;
  const char *name;

  name = fullpath;
  for (; *name; name++)
    hash = hash * 31 + (unsigned char)*name;

  hash %= lo_data->hash_table.size;
  oldhash = hash % (lo_data->hash_table.size / 2);
  if (oldhash >= lo_data->hash_table.split)
    return oldhash;
  else
    return hash;
}

void remap_hash_table(struct lo_data *lo_data) {
  struct node_table *t = &lo_data->hash_table;
  struct lo_inode **nodep;
  struct lo_inode **next;
  struct lo_inode *prev;
  size_t hash;

  if (t->split == t->size / 2)
    return;

  /* split this bucket by recalculating the hash */
  hash = t->split;
  t->split++;

  for (nodep = &t->array[hash]; *nodep != NULL; nodep = next) {
    struct lo_inode *node = *nodep;
    size_t newhash = name_hash(lo_data, node->ino, node->name);

    if (newhash != hash) {
      prev = node->prev;
      *nodep = node->next;
      if (*nodep)
        (*nodep)->prev = prev;

      node->prev = NULL;
      node->next = t->array[newhash];
      if (t->array[newhash])
        (t->array[newhash])->prev = node;
      t->array[newhash] = node;
      next = nodep;
    } else {
      next = &node->next;
    }
  }

  /* If we have reached the splitting to half of the size
   * then double the size of hash table */
  if (t->split == t->size / 2)
    hash_table_resize(t);
}

void remerge_hash_table(struct lo_data *lo_data) {
  struct node_table *t = &lo_data->hash_table;
  int iter;

  /* This means all the hashes would be under the half size
   * of table (so simply make it half) */
  if (t->split == 0)
    hash_table_reduce(t);

  for (iter = 8; t->split > 0 && iter; iter--) {
    struct lo_inode **upper;

    t->split--;
    upper = &t->array[t->split + t->size / 2];
    if (*upper) {
      struct lo_inode **nodep;
      struct lo_inode *prev = NULL;

      for (nodep = &t->array[t->split]; *nodep; nodep = &(*nodep)->next)
        prev = *nodep;

      *nodep = *upper;
      (*upper)->prev = prev;
      *upper = NULL;
      break;
    }
  }
}

/* Function which checks the inode in the hash table
 * by calculating the hash from ino and full path */
struct lo_inode *lookup_lo_inode(struct lo_data *lo_data, struct stat *st,
                                 const char *fullpath) {
  size_t hash = name_hash(lo_data, st->st_ino, fullpath);
  struct lo_inode *node;

  for (node = lo_data->hash_table.array[hash]; node != NULL;
       node = node->next) {
    if ((node->ino == st->st_ino) && (node->dev == st->st_dev) &&
        (strcmp(node->name, fullpath) == 0))
      return node;
  }

  return NULL;
}

/* A function which checks the hash table and returns the lo_inode
 * otherwise a new lo_inode is created and inserted into the hashtable
 * req          --> for the hash_table reference
 * st           --> to check against the ino and dev_id
 *                      when navigating the bucket chain
 * fullpath     --> full path is used to construct the key */
struct lo_inode *find_lo_inode(fuse_req_t req, struct stat *st,
                               char *fullpath) {
  struct lo_data *lo_data;
  struct lo_inode *lo_inode;
  int res;

  lo_data = get_lo_data(req);
  pthread_spin_lock(&lo_data->spinlock);

  lo_inode = lookup_lo_inode(lo_data, st, fullpath);
  if (lo_inode == NULL) {
    /* create the node and insert into hash_table */
    lo_inode = calloc(1, sizeof(struct lo_inode));
    if (!lo_inode)
      goto find_out;
    lo_inode->ino = st->st_ino;
    lo_inode->dev = st->st_dev;
    lo_inode->name = strdup(fullpath);
    /* store this for mapping (debugging) */
    lo_inode->lo_ino = (uintptr_t)lo_inode;
    lo_inode->next = lo_inode->prev = NULL;

    /* insert into hash table */
    res = insert_to_hash_table(lo_data, lo_inode);
    if (res == -1) {
      free(lo_inode->name);
      free(lo_inode);
      lo_inode = NULL;
      goto find_out;
    }
  }
  lo_inode->nlookup++;
find_out:
  pthread_spin_unlock(&lo_data->spinlock);
  return lo_inode;
}
