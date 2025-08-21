# 파일명: seq-wr-1th-1f-4KB.f

set mode quit alldone

set $dir=/mnt/nvme0n1p6
set $iosize=1024k
set $iters=16384

define file name=seqset, path=$dir, size=60g

define process name=seq_writer, instances=1 {
  thread name=seq_thread, memsize=$iosize, instances=1 {
    flowop createfile  name=c1, filesetname=seqset
    flowop write       name=w1, filesetname=seqset, iosize=$iosize, iters=$iters
    flowop closefile   name=cl1
    flowop finishoncount name=fin, value=1
  }
}

create files

system "sync"
system "echo 3 > /proc/sys/vm/drop_caches"

run 1

