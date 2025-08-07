#include <unistd.h>
#include "ops.h"

void stackfs_ll_release(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  (void)ino;

  // StackFS_trace("Release called on name : %s and inode : %llu fd : %d ",
  //            lo_name(req, ino), lo_inode(req, ino)->ino, fi->fh);
  // generate_start_time(req);
  close(fi->fh);
  // generate_end_time(req);
  // populate_time(req);

  fuse_reply_err(req, 0);
}
