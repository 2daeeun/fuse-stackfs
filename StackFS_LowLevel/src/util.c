#include "../include/util.h"
#include "../include/stackfs_info.h"
#include "../include/trace.h"
#include <fuse_opt.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

char banner[4096];

void print_usage(void) {
  printf("예시: sudo ./StackFS_ll -r temp_mount -f -d /mnt/partition_06_4GB\n");
  printf("USAGE : ./StackFS_ll -r <rootDir>|-rootdir=<rootDir> \n");
  printf("[--attrval=<time(secs)>] [--statsdir=<statsDirPath>] \n");
  printf("<mountDir> [FUSE options]\n"); /* For checkPatch.pl */
  printf("<rootDir>  : Root Directory containg the Low Level F/S\n");
  printf("<attrval>  : Time in secs to let kernel know how muh time ");
  printf("the attributes are valid\n"); /* For checkPatch.pl */
  printf("<statsDirPath> : Path for copying any statistics details\n");
  printf("<mountDir> : Mount Directory on to which the F/S should be ");
  printf("mounted\n"); /* For checkPatch.pl */
  printf("Example    : ./StackFS_ll -r rootDir/ mountDir/\n");
}

int64_t print_timer(void) {
  struct timespec tms;

  if (clock_gettime(CLOCK_REALTIME, &tms)) {
    printf("ERROR\n");
    return 0;
  }
  int64_t micros = tms.tv_sec * 1000000;

  micros += tms.tv_nsec / 1000;
  if (tms.tv_nsec % 1000 >= 500)
    ++micros;
  return micros;
}

/* called with file lock */
int print_banner(void) {
  int len;
  int64_t time;
  int pid;
  unsigned long tid;

  banner[0] = '\0';
  time = print_timer();
  pid = getpid();
  tid = syscall(SYS_gettid);
  if (time == 0)
    return -1;
  len =
      sprintf(banner, "Time : %" PRId64 " Pid : %d Tid : %lu ", time, pid, tid);
  (void)len;
  fputs(banner, logfile);
  return 0;
}

int stackfs_process_arg(void *data, const char *arg, int key,
                        struct fuse_args *outargs) {
  struct stackFS_info *s_info = data;

  (void)outargs;
  (void)arg;

  switch (key) {
  case 0:
    s_info->is_help = 1;
    return 0;
  case 1:
    s_info->tracing = 1;
    return 0;
  default:
    return 1;
  }
}
