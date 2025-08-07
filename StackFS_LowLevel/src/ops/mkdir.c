#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include "ops.h"

void stackfs_ll_mkdir(fuse_req_t req, fuse_ino_t parent, const char *name,
                      mode_t mode) {
  int res;
  struct fuse_entry_param e;
  char *fullPath = NULL;
  double attr_val;

  // StackFS_trace("Mkdir called with name : %s, parent ino : %llu",
  //                            name, lo_inode(req, parent)->ino);
  fullPath = (char *)malloc(PATH_MAX);
  construct_full_path(req, parent, fullPath, name);
  attr_val = lo_attr_valid_time(req);

  // generate_start_time(req);
  res = mkdir(fullPath, mode);
  if (res == -1) {
    /* Error occurred while creating the directory */
    if (fullPath)
      free(fullPath);
    // generate_end_time(req);
    // populate_time(req);
    return (void)fuse_reply_err(req, errno);
  }

  /* Assign the stats of the newly created directory */
  memset(&e, 0, sizeof(e));
  e.attr_timeout = attr_val;
  e.entry_timeout = 1.0; /* may be attr_val */
  res = stat(fullPath, &e.attr);
  // generate_end_time(req);
  // populate_time(req);

  if (res == 0) {
    /* insert lo_inode into the hash table */
    struct lo_data *lo_data;
    struct lo_inode *lo_inode;
    lo_inode = calloc(1, sizeof(struct lo_inode));
    if (!lo_inode) {
      if (fullPath)
        free(fullPath);
      return (void)fuse_reply_err(req, errno);
    }

    lo_inode->ino = e.attr.st_ino;
    lo_inode->dev = e.attr.st_dev;
    lo_inode->name = strdup(fullPath);
    /* store this for mapping (debugging) */
    lo_inode->lo_ino = (uintptr_t)lo_inode;
    lo_inode->next = lo_inode->prev = NULL;
    free(fullPath);

    lo_data = get_lo_data(req);
    pthread_spin_lock(&lo_data->spinlock);

    res = insert_to_hash_table(lo_data, lo_inode);

    pthread_spin_unlock(&lo_data->spinlock);

    if (res == -1) {
      free(lo_inode->name);
      free(lo_inode);
      fuse_reply_err(req, EBUSY);
    } else {
      lo_inode->nlookup++;
      e.ino = lo_inode->lo_ino;
      fuse_reply_entry(req, &e);
    }
  } else {
    if (fullPath)
      free(fullPath);
    fuse_reply_err(req, errno);
  }
}
