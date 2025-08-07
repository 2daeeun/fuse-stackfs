#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "ops.h"

void stackfs_ll_rmdir(fuse_req_t req, fuse_ino_t parent, const char *name) {
  int res;
  char *fullPath = NULL;

  // StackFS_trace("rmdir called with name : %s, parent inode : %llu",
  //                            name, lo_inode(req, parent)->ino);
  fullPath = (char *)malloc(PATH_MAX);
  construct_full_path(req, parent, fullPath, name);
  // generate_start_time(req);
  res = rmdir(fullPath);
  // generate_end_time(req);
  // populate_time(req);

  if (res == -1)
    fuse_reply_err(req, errno);
  else
    fuse_reply_err(req, res);

  if (fullPath)
    free(fullPath);
}
