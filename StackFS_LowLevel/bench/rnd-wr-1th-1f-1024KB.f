# 파일명: rnd-wr-1th-1f-4KB.f

set mode quit alldone

set $dir=/mnt/nvme0n1p6
set $nthreads=1
set $iosize=1024k
set $iters=16384

define fileset name=seqset, path=$dir, entries=1, size=16g, dirwidth=1, prealloc

define process name=rnd_writer, instances=1 {
  thread name=seq_thread, memsize=$iosize, instances=$nthreads {
    flowop openfile   name=open1,   filesetname=seqset, fd=1
    flowop write      name=wrand1,  filesetname=seqset, iosize=$iosize, iters=$iters, random, fd=1
    flowop closefile  name=close1, fd=1
    flowop finishoncount name=finish, value=1
  }
}

create files

system "sync"
system "echo 3 > /proc/sys/vm/drop_caches"

run 1

