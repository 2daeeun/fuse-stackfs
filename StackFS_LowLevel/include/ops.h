#ifndef STACKFS_LOWLEVEL_OPS_H
#define STACKFS_LOWLEVEL_OPS_H

#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#define FUSE_USE_VERSION 30

#define TESTING_XATTR 0
#define USE_SPLICE 0

// #include "hash_table.h"
// #include "inode.h"
#include "path_utils.h"
// #include "trace.h"
// #include "util.h"
#include <fuse_lowlevel.h>
#include <sys/stat.h>

/* FUSE low-level operation function prototypes */
void stackfs_ll_lookup(fuse_req_t req, fuse_ino_t parent, const char *name);
void stackfs_ll_getattr(fuse_req_t req, fuse_ino_t ino,
                        struct fuse_file_info *fi);
void stackfs_ll_setattr(fuse_req_t req, fuse_ino_t ino, struct stat *attr,
                        int to_set, struct fuse_file_info *fi);
void stackfs_ll_create(fuse_req_t req, fuse_ino_t parent, const char *name,
                       mode_t mode, struct fuse_file_info *fi);
void stackfs_ll_mkdir(fuse_req_t req, fuse_ino_t parent, const char *name,
                      mode_t mode);
void stackfs_ll_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi);
void stackfs_ll_opendir(fuse_req_t req, fuse_ino_t ino,
                        struct fuse_file_info *fi);
void stackfs_ll_read(fuse_req_t req, fuse_ino_t ino, size_t size, off_t offset,
                     struct fuse_file_info *fi);
void stackfs_ll_readdir(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
                        struct fuse_file_info *fi);
void stackfs_ll_release(fuse_req_t req, fuse_ino_t ino,
                        struct fuse_file_info *fi);
void stackfs_ll_releasedir(fuse_req_t req, fuse_ino_t ino,
                           struct fuse_file_info *fi);
void stackfs_ll_write(fuse_req_t req, fuse_ino_t ino, const char *buf,
                      size_t size, off_t off, struct fuse_file_info *fi);
#if USE_SPLICE
void stackfs_ll_write_buf(fuse_req_t req, fuse_ino_t ino,
                          struct fuse_bufvec *buf, off_t off,
                          struct fuse_file_info *fi);
#endif
void stackfs_ll_unlink(fuse_req_t req, fuse_ino_t parent, const char *name);
void stackfs_ll_rmdir(fuse_req_t req, fuse_ino_t parent, const char *name);
void stackfs_ll_forget(fuse_req_t req, fuse_ino_t ino, uint64_t nlookup);
void stackfs_ll_forget_multi(fuse_req_t req, size_t count,
                             struct fuse_forget_data *forgets);
void stackfs_ll_flush(fuse_req_t req, fuse_ino_t ino,
                      struct fuse_file_info *fi);
void stackfs_ll_statfs(fuse_req_t req, fuse_ino_t ino);
void stackfs_ll_fsync(fuse_req_t req, fuse_ino_t ino, int datasync,
                      struct fuse_file_info *fi);
#if TESTING_XATTR
void stackfs_ll_getxattr(fuse_req_t req, fuse_ino_t ino, const char *name,
                         size_t size);
#endif

#endif /* STACKFS_LOWLEVEL_OPS_H */
