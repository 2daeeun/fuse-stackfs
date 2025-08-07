#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "ops.h"

void stackfs_ll_readdir(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
                        struct fuse_file_info *fi) {
  struct lo_dirptr *d;
  char *buf = NULL;
  char *p = NULL;
  size_t rem;
  int err;
  (void)ino;

  // StackFS_trace("Readdir called on name : %s and inode : %llu",
  //                    lo_name(req, ino), lo_inode(req, ino)->ino);
  d = lo_dirptr(fi);
  buf = malloc(size * sizeof(char));
  if (!buf)
    return (void)fuse_reply_err(req, ENOMEM);

  // generate_start_time(req);
  /* If offset is not same, need to seek it */
  if (off != d->offset) {
    seekdir(d->dp, off);
    d->entry = NULL;
    d->offset = off;
  }
  p = buf;
  rem = size;
  while (1) {
    size_t entsize;
    off_t nextoff;

    if (!d->entry) {
      errno = 0;
      d->entry = readdir(d->dp);
      if (!d->entry) {
        if (errno && rem == size) {
          err = errno;
          goto error;
        }
        break;
      }
    }
    nextoff = telldir(d->dp);

    struct stat st = {
        .st_ino = d->entry->d_ino,
        .st_mode = d->entry->d_type << 12,
    };
    entsize = fuse_add_direntry(req, p, rem, d->entry->d_name, &st, nextoff);
    /* The above function returns the size of the entry even though
     * the copy failed due to smaller buf size, so I'm checking after this
     * function and breaking out in case we exceed the size.
     */
    if (entsize > rem)
      break;

    p += entsize;
    rem -= entsize;

    d->entry = NULL;
    d->offset = nextoff;
  }

  // generate_end_time(req);
  // populate_time(req);
  fuse_reply_buf(req, buf, size - rem);
  free(buf);
  return;

error:
  // generate_end_time(req);
  // populate_time(req);
  free(buf);
  fuse_reply_err(req, err);
}
