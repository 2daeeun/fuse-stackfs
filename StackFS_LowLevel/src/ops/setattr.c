#include "ops.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

void stackfs_ll_setattr(fuse_req_t req, fuse_ino_t ino, struct stat *attr,
                        int to_set, struct fuse_file_info *fi) {
  int res;
  (void)fi;
  struct stat buf;
  double attr_val;

  // StackFS_trace("Setattr called on name : %s and inode : %llu",
  //                    lo_name(req, ino), lo_inode(req, ino)->ino);
  attr_val = lo_attr_valid_time(req);
  // generate_start_time(req);
  if (to_set & FUSE_SET_ATTR_SIZE) {
    /* Truncate */
    res = truncate(lo_name(req, ino), attr->st_size);
    if (res != 0) {
      // generate_end_time(req);
      // populate_time(req);
      return (void)fuse_reply_err(req, errno);
    }
  }

  if (to_set & (FUSE_SET_ATTR_ATIME | FUSE_SET_ATTR_MTIME)) {
    /* Update Time */
    struct utimbuf tv;
    tv.actime = attr->st_atime;
    tv.modtime = attr->st_mtime;
    res = utime(lo_name(req, ino), &tv);
    if (res != 0) {
      // generate_end_time(req);
      // populate_time(req);
      return (void)fuse_reply_err(req, errno);
    }
  }

  memset(&buf, 0, sizeof(buf));
  res = stat(lo_name(req, ino), &buf);
  // generate_end_time(req);
  // populate_time(req);
  if (res != 0)
    return (void)fuse_reply_err(req, errno);

  fuse_reply_attr(req, &buf, attr_val);
}
