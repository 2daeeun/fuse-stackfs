#include <errno.h>
#include <sys/xattr.h>
#include <stdlib.h>
#include "ops.h"

#if TESTING_XATTR
void stackfs_ll_getxattr(fuse_req_t req, fuse_ino_t ino, const char *name, size_t size) {
  int res;

  // StackFS_trace("Function Trace : Getxattr");
  if (size) {
    char *value = (char *)malloc(size);
    // generate_start_time(req);
    res = lgetxattr(lo_name(req, ino), name, value, size);
    // generate_end_time(req);
    // populate_time(req);
    if (res > 0)
      fuse_reply_buf(req, value, res);
    else
      fuse_reply_err(req, errno);
    free(value);
  } else {
    // generate_start_time(req);
    res = lgetxattr(lo_name(req, ino), name, NULL, 0);
    // generate_end_time(req);
    // populate_time(req);
    if (res >= 0)
      fuse_reply_xattr(req, res);
    else
      fuse_reply_err(req, errno);
  }
}
#endif
