#include <unistd.h>
#include "ops.h"

void stackfs_ll_fsync(fuse_req_t req, fuse_ino_t ino, int datasync,
                      struct fuse_file_info *fi) {
  int res;

  // StackFS_trace("Fsync on name : %s, inode : %llu, datasync : %d",
  //     lo_name(req, ino), lo_inode(req, ino)->ino, datasync);
  // generate_start_time(req);
  if (datasync)
    res = fdatasync(fi->fh);
  else
    res = fsync(fi->fh);
  // generate_end_time(req);
  // populate_time(req);

  fuse_reply_err(req, res);
}
