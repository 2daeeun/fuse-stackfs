#include <string.h>
#include <sys/statvfs.h>
#include "ops.h"

void stackfs_ll_statfs(fuse_req_t req, fuse_ino_t ino) {
  int res;
  struct statvfs buf;

  if (ino) {
    // StackFS_trace("Statfs called with name : %s, and inode : %llu",
    //          lo_name(req, ino), lo_inode(req, ino)->ino);
    memset(&buf, 0, sizeof(buf));
    // generate_start_time(req);
    res = statvfs(lo_name(req, ino), &buf);
    // generate_end_time(req);
    // populate_time(req);
  }

  if (!res)
    fuse_reply_statfs(req, &buf);
  else
    fuse_reply_err(req, res);
}
