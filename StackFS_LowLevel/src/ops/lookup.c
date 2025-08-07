#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "ops.h"

void stackfs_ll_lookup(fuse_req_t req, fuse_ino_t parent, const char *name) {
  struct fuse_entry_param e;
  int res;
  char *fullPath = NULL;
  double attr_val;

  // StackFS_trace("Lookup called on name : %s, parent ino : %llu",
  //                                                    name, parent);
  fullPath = (char *)malloc(PATH_MAX);
  construct_full_path(req, parent, fullPath, name);

  attr_val = lo_attr_valid_time(req);
  memset(&e, 0, sizeof(e));
  e.attr_timeout = attr_val;
  e.entry_timeout = 1.0; /* dentry timeout */

  // generate_start_time(req);
  res = stat(fullPath, &e.attr);
  // generate_end_time(req);
  // populate_time(req);

  if (res == 0) {
    struct lo_inode *inode;
    inode = find_lo_inode(req, &e.attr, fullPath);

    if (fullPath)
      free(fullPath);

    if (!inode)
      fuse_reply_err(req, ENOMEM);
    else {
      /* store this address for faster path conversions */
      e.ino = inode->lo_ino;
      fuse_reply_entry(req, &e);
    }
  } else {
    if (fullPath)
      free(fullPath);
    fuse_reply_err(req, ENOENT);
  }
}
