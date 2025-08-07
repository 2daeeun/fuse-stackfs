#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include "ops.h"

void stackfs_ll_opendir(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  DIR *dp;
  struct lo_dirptr *d;

  // StackFS_trace("Opendir called on name : %s and inode : %llu",
  //                    lo_name(req, ino), lo_inode(req, ino)->ino);
  // generate_start_time(req);
  dp = opendir(lo_name(req, ino));
  // generate_end_time(req);
  // populate_time(req);

  if (dp == NULL)
    return (void)fuse_reply_err(req, errno);

  d = malloc(sizeof(struct lo_dirptr));
  d->dp = dp;
  d->offset = 0;
  d->entry = NULL;

  fi->fh = (uintptr_t)d;
  fuse_reply_open(req, fi);
}
