#include <errno.h>
#include "ops.h"

#if USE_SPLICE
void stackfs_ll_write_buf(fuse_req_t req, fuse_ino_t ino, struct fuse_bufvec *buf,
                          off_t off, struct fuse_file_info *fi) {
  int res;
  (void)ino;

  struct fuse_bufvec dst = FUSE_BUFVEC_INIT(fuse_buf_size(buf));
  // StackFS_trace("Splice Write_buf on name : %s, off : %lu, size : %zu",
  //                    lo_name(req, ino), off, buf->buf[0].size);
  generate_start_time(req);
  dst.buf[0].flags = FUSE_BUF_IS_FD | FUSE_BUF_FD_SEEK;
  dst.buf[0].fd = fi->fh;
  dst.buf[0].pos = off;
  res = fuse_buf_copy(&dst, buf, FUSE_BUF_SPLICE_NONBLOCK);
  generate_end_time(req);
  populate_time(req);
  if (res >= 0)
    fuse_reply_write(req, res);
  else
    fuse_reply_err(req, res);
}
#endif
