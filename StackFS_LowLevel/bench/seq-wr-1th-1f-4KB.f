set mode quit alldone

set $dir=/mnt/stackfs/
set $nthreads=1
set $iosize=4k
set $filesize=60g
set $iters=15728640

define file name=seqfile, path=$dir, size=$filesize

define process name=seq_writer, instances=1 {
  thread name=seq_thread, memsize=$iosize, instances=$nthreads {
    flowop createfile  name=c1, filename=seqfile
    flowop write       name=w1, filename=seqfile, iosize=$iosize, iters=$iters
    flowop closefile   name=cl1
    flowop finishoncount name=fin, target=w1, value=$iters
  }
}

create files
system "sync"
system "echo 3 > /proc/sys/vm/drop_caches"
run 10

