#ifndef STACKFS_INFO_H
#define STACKFS_INFO_H

/* main.c, util.c 등에서 공통으로 쓰는 옵션/설정 구조체 */
struct stackFS_info {
  char *rootDir;     /* -r 또는 --rootdir 로 지정된 루트 경로 */
  char *statsDir;    /* --statsdir 로 지정된 통계 디렉토리 */
  double attr_valid; /* --attrval 로 설정된 속성 캐시 유효 시간 */
  int is_help;       /* -h/--help 옵션 여부 */
  int tracing;       /* --tracing 옵션 여부 */
};

#endif /* STACKFS_INFO_H */
