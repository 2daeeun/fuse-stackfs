#include <assert.h>
#include "ops.h"

static void forget_inode(fuse_req_t req, struct lo_inode *inode, uint64_t nlookup) {
  int res;
  assert(inode->nlookup >= nlookup);
  inode->nlookup -= nlookup;
  if (!inode->nlookup)
    res = delete_from_hash_table(get_lo_data(req), inode);
  (void)res;
}

void stackfs_ll_forget(fuse_req_t req, fuse_ino_t ino, uint64_t nlookup) {
  struct lo_inode *inode = lo_inode(req, ino);

  // generate_start_time(req);
  // StackFS_trace("Forget name : %s, inode : %llu and lookup count : %llu",
  //                            inode->name, inode->ino, nlookup);
  forget_inode(req, inode, nlookup);
  // generate_end_time(req);
  // populate_time(req);

  fuse_reply_none(req);
}

void stackfs_ll_forget_multi(fuse_req_t req, size_t count,
                             struct fuse_forget_data *forgets) {
  size_t i;
  struct lo_inode *inode;
  fuse_ino_t ino;
  uint64_t nlookup;

  // generate_start_time(req);
  // StackFS_trace("Batch Forget count : %zu", count);
  for (i = 0; i < count; i++) {
    ino = forgets[i].ino;
    nlookup = forgets[i].nlookup;
    inode = lo_inode(req, ino);
    // StackFS_trace("Forget %zu name : %s, lookup count : %llu",
    //                          i, inode->name, nlookup);
    forget_inode(req, inode, nlookup);
  }
  // generate_end_time(req);
  // populate_time(req);

  fuse_reply_none(req);
}
