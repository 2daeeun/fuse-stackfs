#include "../include/inode.h"
#include <limits.h>
#include <string.h>

/* fi->fh에서 lo_dirptr 반환 */
struct lo_dirptr *lo_dirptr(struct fuse_file_info *fi) {
  return (struct lo_dirptr *)(uintptr_t)fi->fh;
}

/* req_userdata에서 lo_data 반환 */
struct lo_data *get_lo_data(fuse_req_t req) {
  return (struct lo_data *)fuse_req_userdata(req);
}

/* ino에 해당하는 lo_inode 반환 */
struct lo_inode *lo_inode(fuse_req_t req, fuse_ino_t ino) {
  if (ino == FUSE_ROOT_ID)
    return &get_lo_data(req)->root;
  return (struct lo_inode *)(uintptr_t)ino;
}

/* lo_inode->name 반환 */
char *lo_name(fuse_req_t req, fuse_ino_t ino) {
  return lo_inode(req, ino)->name;
}

/* 하위 FUSE FS에 전달할 inode 번호 반환 */
ino_t get_lower_fuse_inode_no(fuse_req_t req, fuse_ino_t ino) {
  return lo_inode(req, ino)->lo_ino;
}

/* 사용자 FUSE 파일시스템에 전달되는 inode 번호 */
// static ino_t get_higher_fuse_inode_no(fuse_req_t req, fuse_ino_t ino) {
//     return lo_inode(req, ino)->ino;
// }

/* 속성 캐시 유효 시간 반환 */
double lo_attr_valid_time(fuse_req_t req) {
  return get_lo_data(req)->attr_valid;
}

/* 전체 경로 생성: 부모 경로 + "/" + 파일명 */
void construct_full_path(fuse_req_t req, fuse_ino_t ino, char *fpath,
                         const char *path) {
  strcpy(fpath, lo_name(req, ino));
  strcat(fpath, "/");
  strncat(fpath, path, PATH_MAX);
}
