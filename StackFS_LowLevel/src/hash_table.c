#include "../include/hash_table.h"
#include "../include/path_utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*=============Hash Table 구현==========================*/

/* 해시 테이블 초기화 */
int hash_table_init(struct node_table *t) {
  t->size = HASH_TABLE_MIN_SIZE;
  t->array = (struct lo_inode **)calloc(1, sizeof(struct lo_inode *) * t->size);
  if (t->array == NULL) {
    fprintf(stderr, "fuse: 메모리 할당 실패\n");
    return -1;
  }
  t->use = 0;
  t->split = 0;

  return 0;
}

/* 해시 테이블 해제 */
void hash_table_destroy(struct node_table *t) { free(t->array); }

/* 해시 테이블 크기 확장 (버킷 개수 ×2) */
int hash_table_resize(struct node_table *t) {
  size_t newsize = t->size * 2;
  struct lo_inode **newarray;

  newarray = realloc(t->array, newsize * sizeof(*newarray));
  if (!newarray) {
    fprintf(stderr, "fuse: 메모리 할당 실패\n");
    return -1;
  }
  /* 새로 확장된 버킷 영역 초기화 */
  memset(newarray + t->size, 0, t->size * sizeof(*newarray));
  t->array = newarray;
  t->size = newsize;
  t->split = 0;
  return 0;
}

/* 해시 테이블 크기 축소 */
void hash_table_reduce(struct node_table *t) {
  size_t newsize = t->size / 2;
  void *newarray;

  if (newsize < HASH_TABLE_MIN_SIZE)
    return;

  newarray = realloc(t->array, newsize * sizeof(*t->array));
  if (newarray != NULL)
    t->array = newarray;

  t->size = newsize;
  t->split = t->size / 2;
}

/* 해시 테이블에 노드 추가 */
int insert_to_hash_table(struct lo_data *lo_data, struct lo_inode *lo_inode) {
  size_t hash = name_hash(lo_data, lo_inode->ino, lo_inode->name);

  lo_inode->next = lo_data->hash_table.array[hash];
  if (lo_data->hash_table.array[hash])
    (lo_data->hash_table.array[hash])->prev = lo_inode;
  lo_data->hash_table.array[hash] = lo_inode;
  lo_data->hash_table.use++;

  if (lo_data->hash_table.use >= lo_data->hash_table.size / 2)
    remap_hash_table(lo_data);

  return 0;
}

/* 해시 테이블에서 노드 삭제 */
int delete_from_hash_table(struct lo_data *lo_data, struct lo_inode *lo_inode) {
  struct lo_inode *prev, *next;
  prev = next = NULL;
  size_t hash = 0;

  pthread_spin_lock(&lo_data->spinlock);

  prev = lo_inode->prev;
  next = lo_inode->next;

  if (prev) {
    prev->next = next;
    if (next)
      next->prev = prev;
    goto del_out;
  } else {
    hash = name_hash(lo_data, lo_inode->ino, lo_inode->name);
    if (next)
      next->prev = NULL;
    lo_data->hash_table.array[hash] = next;
  }

del_out:
  /* free the lo_inode */
  lo_inode->prev = lo_inode->next = NULL;
  free(lo_inode->name);
  free(lo_inode);

  lo_data->hash_table.use--;
  if (lo_data->hash_table.use < lo_data->hash_table.size / 4)
    remerge_hash_table(lo_data);

  pthread_spin_unlock(&lo_data->spinlock);
  return 0;
}

/* 해시 테이블의 모든 노드 메모리 해제 */
void free_hash_table(struct lo_data *lo_data) {
  struct lo_inode *node, *next;
  int i;

  for (i = 0; i < lo_data->hash_table.size; i++) {
    node = lo_data->hash_table.array[i];
    while (node) {
      next = node->next;
      /* free up the node */
      free(node->name);
      free(node);
      node = next;
    }
  }
}
