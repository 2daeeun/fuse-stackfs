#include <stdlib.h>
#include <dirent.h>
#include "ops.h"

void stackfs_ll_releasedir(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
  struct lo_dirptr *d;
  (void)ino;

  // StackFS_trace("Releasedir called on name : %s and inode : %llu",
  //                    lo_name(req, ino), lo_inode(req, ino)->ino);
  d = lo_dirptr(fi);
  // generate_start_time(req);
  closedir(d->dp);
  // generate_end_time(req);
  // populate_time(req);
  free(d);
  fuse_reply_err(req, 0);
}
