#include <errno.h>
#include <unistd.h>
#include "ops.h"

void stackfs_ll_write(fuse_req_t req, fuse_ino_t ino, const char *buf,
                      size_t size, off_t off, struct fuse_file_info *fi) {
  int res;
  (void)ino;

  // StackFS_trace("Write name : %s, inode : %llu, off : %lu, size : %zu",
  //            lo_name(req, ino), lo_inode(req, ino)->ino, off, size);
  // generate_start_time(req);
  res = pwrite(fi->fh, buf, size, off);
  // generate_end_time(req);
  // populate_time(req);

  if (res == -1)
    return (void)fuse_reply_err(req, errno);

  fuse_reply_write(req, res);
}
