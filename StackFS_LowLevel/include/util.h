#ifndef STACKFS_LOWLEVEL_UTIL_H
#define STACKFS_LOWLEVEL_UTIL_H

#include <stdint.h> /* for int64_t */
struct fuse_args;   /* forward declare struct fuse_args */

/* Function prototypes for utility and argument processing */
void print_usage(void);
int print_banner(void);
int64_t print_timer(void);
int stackfs_process_arg(void *data, const char *arg, int key,
                        struct fuse_args *outargs);

#endif /* STACKFS_LOWLEVEL_UTIL_H */
