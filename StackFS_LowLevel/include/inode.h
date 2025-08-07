#ifndef STACKFS_LOWLEVEL_INODE_H
#define STACKFS_LOWLEVEL_INODE_H

#include "hash_table.h"
#include <dirent.h>
#include <fuse_lowlevel.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/types.h>

/* 캐시된 inode 노드
 * 로컬 캐시에 유지되는 노드 구조체로, ino 번호를 전체 경로에 매핑하며,
 * 해당 주소는 해시 테이블 값의 일부로 저장됨 */
struct lo_inode {
  struct lo_inode *next;
  struct lo_inode *prev;
  char *name;       /* 실제 ext4 경로의 전체 경로 */
  ino_t ino;        /* 원본 ext4 inode 번호 */
  dev_t dev;        /* ext4 파일시스템 장치 번호 */
  ino_t lo_ino;     /* 하위 FUSE 레이어에 사용되는 inode 번호 */
  uint64_t nlookup; /* 조회 횟수 */
};

/* FUSE 요청별 데이터 구조
 * 해시 테이블을 저장하는 데 사용되며
 * req 구조체의 일부로 항상 포함되는 구조체 */
struct lo_data {
  struct node_table hash_table; /* inode → 경로 캐시 */
  pthread_spinlock_t spinlock;  /* hash_table 보호 */
  struct lo_inode root;         /* 루트 inode('/') */
  double attr_valid;            /* 속성 캐시 유효 시간 */
};

/* 디렉터리 읽기 포인터 */
struct lo_dirptr {
  DIR *dp;              /* 디렉터리 스트림 */
  struct dirent *entry; /* 현재 항목 */
  off_t offset;         /* 오프셋 */
};

/* Prototypes for inode-related helper functions */
struct lo_dirptr *lo_dirptr(struct fuse_file_info *fi);
struct lo_data *get_lo_data(fuse_req_t req);
struct lo_inode *lo_inode(fuse_req_t req, fuse_ino_t ino);
char *lo_name(fuse_req_t req, fuse_ino_t ino);
ino_t get_lower_fuse_inode_no(fuse_req_t req, fuse_ino_t ino);
double lo_attr_valid_time(fuse_req_t req);
void construct_full_path(fuse_req_t req, fuse_ino_t ino, char *fpath,
                         const char *path);

#endif /* STACKFS_LOWLEVEL_INODE_H */
