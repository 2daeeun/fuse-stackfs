#include <errno.h>
#include <fcntl.h>
#include "ops.h"

void stackfs_ll_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  int fd;

  // generate_start_time(req);
  fd = open(lo_name(req, ino), fi->flags);
  // generate_end_time(req);
  // populate_time(req);

  // StackFS_trace("Open called on name : %s and fuse inode : %llu kernel inode
  // : %llu fd : %d",           lo_name(req, ino), get_higher_fuse_inode_no(req,
  // ino),
  // get_lower_fuse_inode_no(req, ino), fd);
  // StackFS_trace("Open name : %s and inode : %llu", lo_name(req, ino),
  //               get_lower_fuse_inode_no(req, ino));

  if (fd == -1)
    return (void)fuse_reply_err(req, errno);

  fi->fh = fd;
  fuse_reply_open(req, fi);
}
