#include <errno.h>
#include <sys/stat.h>
#include "ops.h"

void stackfs_ll_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  int res;
  struct stat buf;
  (void)fi;
  double attr_val;

  // StackFS_trace("Getattr called on name : %s and inode : %llu",
  //                    lo_name(req, ino), lo_inode(req, ino)->ino);
  attr_val = lo_attr_valid_time(req);
  // generate_start_time(req);
  res = stat(lo_name(req, ino), &buf);
  // generate_end_time(req);
  // populate_time(req);
  if (res == -1)
    return (void)fuse_reply_err(req, errno);

  fuse_reply_attr(req, &buf, attr_val);
}
