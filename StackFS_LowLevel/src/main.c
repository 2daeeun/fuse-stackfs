#include "../include/hash_table.h"
#include "../include/inode.h"
#include "../include/ops.h"
#include "../include/stackfs_info.h"
#include "../include/trace.h"
#include "../include/util.h"
#include <errno.h>
#include <fuse.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// /* Structure to hold StackFS command-line options */
// struct stackFS_info {
//   char *rootDir;
//   char *statsDir;    /* Path to copy any statistics details */
//   double attr_valid; /* Time in secs for attribute validation */
//   int is_help;
//   int tracing;
// };

#define STACKFS_OPT(t, p) {t, offsetof(struct stackFS_info, p), 1}

static const struct fuse_opt stackfs_opts[] = {
    STACKFS_OPT("-r %s", rootDir),
    STACKFS_OPT("--rootdir=%s", rootDir),
    STACKFS_OPT("--statsdir=%s", statsDir),
    STACKFS_OPT("--attrval=%lf", attr_valid),
    FUSE_OPT_KEY("--tracing", 1),
    FUSE_OPT_KEY("-h", 0),
    FUSE_OPT_KEY("--help", 0),
    FUSE_OPT_END};

static struct fuse_lowlevel_ops hello_ll_oper = {
    .lookup = stackfs_ll_lookup,
    .getattr = stackfs_ll_getattr,
    .statfs = stackfs_ll_statfs,
    .setattr = stackfs_ll_setattr,
    .flush = stackfs_ll_flush,
    .fsync = stackfs_ll_fsync,
#if TESTING_XATTR
    .getxattr = stackfs_ll_getxattr,
#endif
    .forget = stackfs_ll_forget,
    .forget_multi = stackfs_ll_forget_multi,
    .create = stackfs_ll_create,
    .open = stackfs_ll_open,
    .read = stackfs_ll_read,
    .write = stackfs_ll_write,
#if USE_SPLICE
    .write_buf = stackfs_ll_write_buf,
#endif
    .release = stackfs_ll_release,
    .unlink = stackfs_ll_unlink,
    .mkdir = stackfs_ll_mkdir,
    .rmdir = stackfs_ll_rmdir,
    .opendir = stackfs_ll_opendir,
    .readdir = stackfs_ll_readdir,
    .releasedir = stackfs_ll_releasedir};

int main(int argc, char **argv) {
  int res = 0, err = 0;
  char *rootDir = NULL;
  char *statsDir = NULL;
  char *resolved_statsDir = NULL;
  char *resolved_rootdir_path = NULL;
  int multithreaded;

  struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
  /* Default attr valid time is 1 sec */
  struct stackFS_info s_info = {NULL, NULL, 1.0, 0, 0};

  res = fuse_opt_parse(&args, &s_info, stackfs_opts, stackfs_process_arg);
  if (res) {
    printf("Failed to parse arguments\n");
    return -1;
  }

  if (s_info.is_help) {
    print_usage();
    return 0;
  }

  if (!s_info.rootDir) {
    printf("Root Directory is mandatory\n");
    print_usage();
    return -1;
  }

  if (s_info.statsDir) {
    statsDir = s_info.statsDir;
    resolved_statsDir = realpath(statsDir, NULL);
    if (resolved_statsDir == NULL) {
      printf("There is a problem in resolving the stats ");
      printf("Directory passed %s\n", statsDir);
      perror("Error");
      res = -1;
      goto out1;
    }
  }

  rootDir = s_info.rootDir;
  struct lo_data *lo = NULL;

  if (rootDir) {
    lo = (struct lo_data *)calloc(1, sizeof(struct lo_data));
    if (!lo) {
      fprintf(stderr, "fuse: memory allocation failed\n");
      res = -1;
      goto out2; /* free the resolved_statsDir */
    }
    resolved_rootdir_path = realpath(rootDir, NULL);
    if (!resolved_rootdir_path) {
      printf("There is a problem in resolving the root ");
      printf("Directory Passed %s\n", rootDir);
      perror("Error");
      res = -1;
      goto out3; /* free both resolved_statsDir, lo */
    }
    if (res == 0) {
      (lo->root).name = resolved_rootdir_path;
      (lo->root).ino = FUSE_ROOT_ID;
      (lo->root).nlookup = 2;
      (lo->root).next = (lo->root).prev = NULL;
      lo->attr_valid = s_info.attr_valid;
      /* Initialise the hash table and assign */
      res = hash_table_init(&lo->hash_table);
      if (res == -1)
        goto out4;
      /* Initialise the spin lock for table */
      pthread_spin_init(&(lo->spinlock), 0);
    }
  } else {
    res = -1;
    goto out2;
  }

  struct fuse_chan *ch;
  char *mountpoint;

  /* foreground 변수를 추가하여 데몬화 여부 판단 가능하게 수정 */
  int foreground = 0;
  res = fuse_parse_cmdline(&args, &mountpoint, &multithreaded, &foreground);
  if (res == -1 || mountpoint == NULL) {
    fprintf(stderr, "Error parsing command line arguments\n");
    fuse_opt_free_args(&args);
    res = -1;
    goto out4;
  }

  /* Initialise the spinlock before the logfile creation */
  pthread_spin_init(&spinlock, 0);

  if (s_info.tracing) {
    err = log_open(resolved_statsDir);
    if (err)
      printf("No log file created(but not a fatle error, ");
    printf("so proceeding)\n");
  } else
    printf("No tracing\n");

  printf("Multi Threaded : %d\n", multithreaded);

  if (res != -1) {
    ch = fuse_mount(mountpoint, &args);
    if (!ch) {
      fprintf(stderr, "Error: Failed to mount at %s (errno=%d, %s)\n",
              mountpoint, errno, strerror(errno));
      fuse_opt_free_args(&args);
      return 1;
    }

    struct fuse_session *se;
    printf("Mounted Successfully\n");
    se = fuse_lowlevel_new(&args, &hello_ll_oper, sizeof(hello_ll_oper), lo);
    if (se) {
      if (fuse_set_signal_handlers(se) != -1) {
        fuse_session_add_chan(se, ch);
        if (resolved_statsDir)
          ; // fuse_session_add_statsDir(se, resolved_statsDir);
        if (multithreaded)
          err = fuse_session_loop_mt(se);
        else
          err = fuse_session_loop(se);
        (void)err;

        fuse_remove_signal_handlers(se);
        // fuse_session_remove_statsDir(se);
        fuse_session_remove_chan(ch);
      }
      fuse_session_destroy(se);
    }
    StackFS_trace("Function Trace : Unmount");
    fuse_unmount(mountpoint, ch);
  }

  /* free the arguments */
  fuse_opt_free_args(&args);

  /* destroy the lock protecting the hash table */
  pthread_spin_destroy(&(lo->spinlock));

  /* free up the hash table */
  free_hash_table(lo);

  /* destroy the hash table */
  hash_table_destroy(&lo->hash_table);

  /* destroy the lock protecting the log file */
  pthread_spin_destroy(&spinlock);

  /* close the log file (if any) */
  log_close();

out4:
  if (resolved_rootdir_path)
    free(resolved_rootdir_path);
out3:
  if (lo)
    free(lo);
out2:
  if (resolved_statsDir)
    free(resolved_statsDir);
out1:
  return res;
}
