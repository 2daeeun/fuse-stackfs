#include "ops.h"

void stackfs_ll_flush(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  int err;

  // StackFS_trace("Flush called on name : %s and inode : %llu",
  //                    lo_name(req, ino), lo_inode(req, ino)->ino);
  // generate_start_time(req);
  err = 0;
  // generate_end_time(req);
  // populate_time(req);
  fuse_reply_err(req, err);
}
