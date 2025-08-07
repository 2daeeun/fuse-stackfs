#ifndef STACKFS_LOWLEVEL_PATH_UTILS_H
#define STACKFS_LOWLEVEL_PATH_UTILS_H

#include "hash_table.h"
#include "inode.h"
#include <stddef.h>

/* forward declare struct stat for function prototypes */
struct stat;

/* Path and hash-related helper function prototypes */
size_t name_hash(struct lo_data *lo_data, fuse_ino_t ino, const char *fullpath);
struct lo_inode *lookup_lo_inode(struct lo_data *lo_data, struct stat *st,
                                 const char *fullpath);
struct lo_inode *find_lo_inode(fuse_req_t req, struct stat *st, char *fullpath);
void remap_hash_table(struct lo_data *lo_data);
void remerge_hash_table(struct lo_data *lo_data);

#endif /* STACKFS_LOWLEVEL_PATH_UTILS_H */
