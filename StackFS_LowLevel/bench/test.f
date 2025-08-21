# seq-wr-1th-1f-4KB-60GB.f
# 4KB 쓰기, 60GB, 1 thread, 1 file

set mode quit alldone

# 경로/변수
set $dir=/mnt/stackfs         # Ext4 측정 시 /mnt/nvme0n1p6 로 변경
set $iosize=4k
set $filesize=16g
set $nthreads=1
set $nfiles=1

set $iters=4194304

# (선택) 실행 전 캐시 초기화
system "sync"
system "echo 3 > /proc/sys/vm/drop_caches"

# 단일 파일 대상
define fileset name=seqset, path=$dir, size=$filesize, entries=$nfiles, prealloc=0, reuse=0

# 프로세스/스레드
define process name=seq_writer, instances=1
{
  thread name=writer, instances=$nthreads
  {
    flowop createfile  name=create1,     filesetname=seqset
    flowop appendfile  name=wr,          filesetname=seqset, iosize=$iosize, iters=$iters
    flowop closefile   name=close1

    # wr(flowop) 이 $iters 만큼 완료되면 종료
    flowop finishoncount name=finish, value=$iters, target=wr
  }
}

# 실행
run 86400
