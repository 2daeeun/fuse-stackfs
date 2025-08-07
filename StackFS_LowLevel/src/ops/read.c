#include "ops.h"
#include "trace.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void stackfs_ll_read(fuse_req_t req, fuse_ino_t ino, size_t size, off_t offset,
                     struct fuse_file_info *fi) {
  int res;
  (void)ino;
  // struct timespec start, end;
  // long time;
  // long time_sec;

  StackFS_trace("StackFS Read start on inode : %llu",
                get_lower_fuse_inode_no(req, ino));
  if (USE_SPLICE) {
    struct fuse_bufvec buf = FUSE_BUFVEC_INIT(size);
    // StackFS_trace("Splice Read name : %s, off : %lu, size : %zu",
    //                  lo_name(req, ino), offset, size);
    // generate_start_time(req);
    buf.buf[0].flags = FUSE_BUF_IS_FD | FUSE_BUF_FD_SEEK;
    buf.buf[0].fd = fi->fh;
    buf.buf[0].pos = offset;
    // generate_end_time(req);
    // populate_time(req);
    fuse_reply_data(req, &buf, FUSE_BUF_SPLICE_MOVE);
  } else {
    char *buf;
    // StackFS_trace("Read on name : %s, Kernel inode : %llu, fuse inode : %llu,
    // off : %lu, size : %zu",                  lo_name(req, ino),
    // get_lower_fuse_inode_no(req,
    // ino), get_higher_fuse_inode_no(req, ino), offset, size);
    buf = (char *)malloc(size);
    // generate_start_time(req);
    // clock_gettime(CLOCK_MONOTONIC, &start);
    res = pread(fi->fh, buf, size, offset);
    // clock_gettime(CLOCK_MONOTONIC, &end);
    // generate_end_time(req);
    // populate_time(req);
    // time_sec = end.tv_sec - start.tv_sec;
    // time = end.tv_nsec - start.tv_nsec;
    // time_sec *= 1000000000;
    // time += time_sec;
    // StackFS_trace("Read inode : %llu off : %lu size : %zu diff : %llu",
    // get_lower_fuse_inode_no(req, ino), offset, size, time);
    if (res == -1)
      return (void)fuse_reply_err(req, errno);
    res = fuse_reply_buf(req, buf, res);
    free(buf);
  }
  StackFS_trace("StackFS Read end on inode : %llu",
                get_lower_fuse_inode_no(req, ino));
}
