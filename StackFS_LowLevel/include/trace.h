#ifndef STACKFS_LOWLEVEL_TRACE_H
#define STACKFS_LOWLEVEL_TRACE_H

#include <pthread.h>
#include <stdio.h>

/* Global log file and spinlock for tracing (declared in trace.c) */
extern FILE *logfile;
extern pthread_spinlock_t spinlock;

/* Function prototypes for tracing and logging */
int log_open(char *statsDir);
void log_close(void);
void StackFS_trace(const char *format, ...);

#endif /* STACKFS_LOWLEVEL_TRACE_H */
