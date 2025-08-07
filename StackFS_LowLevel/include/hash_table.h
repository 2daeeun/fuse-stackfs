#ifndef STACKFS_LOWLEVEL_HASH_TABLE_H
#define STACKFS_LOWLEVEL_HASH_TABLE_H

/* 전방 선언: 이 두 타입은 나중에 inode.h에서 정의됩니다 */
struct lo_data;
struct lo_inode;

// #include "inode.h"
#include <stddef.h>

#define HASH_TABLE_MIN_SIZE 8192 /* 초기 버킷 개수 */

/* 해시 테이블 버킷 및 크기 정보 */
struct node_table {
  struct lo_inode **array; /* 키와 값을 저장하는 버킷 배열 */
  size_t use;              /* 현재 사용된 버킷 수 */
  size_t size;  /* 해시 테이블의 최대 크기 (초기값은 HASH_TABLE_MIN_SIZE) */
  size_t split; /* 테이블 크기 조정 시 사용하는 인덱스(fuse-lib 방식) */
};

/* Hash table management API */
int hash_table_init(struct node_table *t);
void hash_table_destroy(struct node_table *t);
void free_hash_table(struct lo_data *lo_data);
int insert_to_hash_table(struct lo_data *lo_data, struct lo_inode *lo_inode);
int delete_from_hash_table(struct lo_data *lo_data, struct lo_inode *lo_inode);
/* Internal resizing functions (exposed for relocation helpers) */
int hash_table_resize(struct node_table *t);
void hash_table_reduce(struct node_table *t);

#endif /* STACKFS_LOWLEVEL_HASH_TABLE_H */
