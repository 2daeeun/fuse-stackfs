### Ext4

sudo filebench -f seq-wr-1th-1f-1024KB.f
[sudo] password for leedaeeun: 
Filebench Version 1.4.9.1
1010296: 0.000: Allocated 170MB of shared memory
1010296: 0.000: Creating/pre-allocating files and filesets
1010296: 0.000: File seqset: 61440.000MB
1010296: 0.003: Removed any existing file seqset in 1 seconds
1010296: 0.003: Creating file seqset...
1010296: 0.003: Preallocated 0 of 1 of file seqset in 1 seconds
1010296: 0.003: waiting for fileset pre-allocation to finish
1010296: 0.003: Running 'sync'
1010296: 0.008: Running 'echo 3 > /proc/sys/vm/drop_caches'
1010296: 0.137: Attempting to create fileset more than once, ignoring
1010301: 0.137: Starting 1 seq_writer instances
1010302: 0.141: Starting 1 seq_thread threads
1010296: 1.141: Running...
1010296: 8.142: Run took 7 seconds...
1010296: 8.143: Per-Operation Breakdown
fin                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
cl1                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
w1                   16384ops     2340ops/s 2340.3mb/s      0.4ms/op      326us/op-cpu [0ms - 303ms]
c1                   1ops        0ops/s   0.0mb/s      1.8ms/op        0us/op-cpu [1ms - 1ms]
1010296: 8.143: IO Summary: 16386 ops, 2340.554 ops/s, (0/2340 r/w), 2340.3mb/s,    596us cpu/op,   0.4ms latency
1010296: 8.143: Shutting down processes


sudo filebench -f seq-rd-1th-1f-1024KB.f 
Filebench Version 1.4.9.1
1012056: 0.000: Allocated 170MB of shared memory
1012056: 0.000: Creating/pre-allocating files and filesets
1012056: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
1012056: 0.004: Removed any existing fileset seqset in 1 seconds
1012056: 0.004: making tree for filset /mnt/nvme0n1p6/seqset
1012056: 0.004: Creating fileset seqset...
1012056: 0.587: Preallocated 1 of 1 of fileset seqset in 1 seconds
1012056: 0.587: waiting for fileset pre-allocation to finish
1012056: 0.587: Running 'sync'
1012056: 1.092: Running 'echo 3 > /proc/sys/vm/drop_caches'
1012056: 1.347: Attempting to create fileset more than once, ignoring
1012137: 1.347: Starting 1 seq_reader instances
1012138: 1.350: Starting 1 seq_thread threads
1012056: 2.350: Running...
1012056: 5.351: Run took 3 seconds...
1012056: 5.351: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
read1                16385ops     5461ops/s 5457.6mb/s      0.2ms/op      146us/op-cpu [0ms - 2ms]
open1                1ops        0ops/s   0.0mb/s      0.1ms/op        0us/op-cpu [0ms - 0ms]
1012056: 5.351: IO Summary: 16387 ops, 5461.896 ops/s, (5461/0 r/w), 5457.6mb/s,    180us cpu/op,   0.2ms latency
1012056: 5.351: Shutting down processes



sudo filebench -f rnd-wr-1th-1f-1024KB.f 
Filebench Version 1.4.9.1
1013736: 0.000: Allocated 170MB of shared memory
1013736: 0.001: Creating/pre-allocating files and filesets
1013736: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
1013736: 0.004: Removed any existing fileset seqset in 1 seconds
1013736: 0.004: making tree for filset /mnt/nvme0n1p6/seqset
1013736: 0.004: Creating fileset seqset...
1013736: 0.569: Preallocated 1 of 1 of fileset seqset in 1 seconds
1013736: 0.569: waiting for fileset pre-allocation to finish
1013736: 0.569: Running 'sync'
1013736: 1.067: Running 'echo 3 > /proc/sys/vm/drop_caches'
1013736: 1.311: Attempting to create fileset more than once, ignoring
1013784: 1.311: Starting 1 rnd_writer instances
1013785: 1.315: Starting 1 seq_thread threads
1013736: 2.316: Running...
1013736: 6.316: Run took 4 seconds...
1013736: 6.317: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
wrand1               16384ops     4096ops/s 4095.6mb/s      0.2ms/op      179us/op-cpu [0ms - 128ms]
open1                1ops        0ops/s   0.0mb/s      0.1ms/op        0us/op-cpu [0ms - 0ms]
1013736: 6.317: IO Summary: 16386 ops, 4096.090 ops/s, (0/4096 r/w), 4095.6mb/s,    270us cpu/op,   0.2ms latency
1013736: 6.317: Shutting down processes


sudo filebench -f rnd-rd-1th-1f-1024KB.f 
Filebench Version 1.4.9.1
1015002: 0.000: Allocated 170MB of shared memory
1015002: 0.000: Creating/pre-allocating files and filesets
1015002: 0.000: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
1015002: 0.003: Removed any existing fileset seqset in 1 seconds
1015002: 0.003: making tree for filset /mnt/nvme0n1p6/seqset
1015002: 0.003: Creating fileset seqset...
1015002: 0.555: Preallocated 1 of 1 of fileset seqset in 1 seconds
1015002: 0.555: waiting for fileset pre-allocation to finish
1015002: 0.555: Running 'sync'
1015002: 1.058: Running 'echo 3 > /proc/sys/vm/drop_caches'
1015002: 1.355: Attempting to create fileset more than once, ignoring
1015046: 1.355: Starting 1 rnd_reader instances
1015047: 1.364: Starting 1 seq_thread threads
1015002: 2.364: Running...
1015002: 7.365: Run took 5 seconds...
1015002: 7.366: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
rrand1               16384ops     3276ops/s 3276.4mb/s      0.3ms/op      220us/op-cpu [0ms - 2ms]
open1                1ops        0ops/s   0.0mb/s      0.2ms/op        0us/op-cpu [0ms - 0ms]
1015002: 7.366: IO Summary: 16386 ops, 3276.778 ops/s, (3276/0 r/w), 3276.4mb/s,    294us cpu/op,   0.3ms latency
1015002: 7.366: Shutting down processes


### StackfsBase

sudo filebench -f seq-wr-1th-1f-1024KB.f
Filebench Version 1.4.9.1
1017047: 0.000: Allocated 170MB of shared memory
1017047: 0.000: Creating/pre-allocating files and filesets
1017047: 0.001: File seqset: 61440.000MB
1017047: 0.008: Removed any existing file seqset in 1 seconds
1017047: 0.008: Creating file seqset...
1017047: 0.008: Preallocated 0 of 1 of file seqset in 1 seconds
1017047: 0.008: waiting for fileset pre-allocation to finish
1017047: 0.008: Running 'sync'
1017047: 0.012: Running 'echo 3 > /proc/sys/vm/drop_caches'
1017047: 0.132: Attempting to create fileset more than once, ignoring
1017053: 0.132: Starting 1 seq_writer instances
1017054: 0.136: Starting 1 seq_thread threads
1017047: 1.136: Running...
1017047: 50.140: Run took 49 seconds...
1017047: 50.141: Per-Operation Breakdown
fin                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
cl1                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
w1                   16384ops      334ops/s 334.3mb/s      2.9ms/op      690us/op-cpu [2ms - 26ms]
c1                   1ops        0ops/s   0.0mb/s      4.4ms/op        0us/op-cpu [4ms - 4ms]
1017047: 50.141: IO Summary: 16386 ops, 334.382 ops/s, (0/334 r/w), 334.3mb/s,   7419us cpu/op,   2.9ms latency
1017047: 50.141: Shutting down processes


sudo filebench -f seq-rd-1th-1f-1024KB.f 
Filebench Version 1.4.9.1
1020277: 0.000: Allocated 170MB of shared memory
1020277: 0.001: Creating/pre-allocating files and filesets
1020277: 0.002: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
1020277: 0.148: Removed any existing fileset seqset in 1 seconds
1020277: 0.148: making tree for filset /mnt/nvme0n1p6/seqset
1020277: 0.149: Creating fileset seqset...
1020277: 5.893: Preallocated 1 of 1 of fileset seqset in 6 seconds
1020277: 5.893: waiting for fileset pre-allocation to finish
1020277: 5.893: Running 'sync'
1020277: 6.341: Running 'echo 3 > /proc/sys/vm/drop_caches'
1020277: 6.752: Attempting to create fileset more than once, ignoring
1020512: 6.752: Starting 1 seq_reader instances
1020513: 6.756: Starting 1 seq_thread threads
1020277: 7.756: Running...
1020277: 11.757: Run took 4 seconds...
1020277: 11.758: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.2ms/op        0us/op-cpu [0ms - 0ms]
read1                16385ops     4096ops/s 4093.1mb/s      0.2ms/op      154us/op-cpu [0ms - 3ms]
open1                1ops        0ops/s   0.0mb/s      1.7ms/op        0us/op-cpu [1ms - 1ms]
1020277: 11.758: IO Summary: 16387 ops, 4096.300 ops/s, (4096/0 r/w), 4093.1mb/s,    349us cpu/op,   0.2ms latency
1020277: 11.758: Shutting down processes


sudo filebench -f rnd-wr-1th-1f-1024KB.f 
Filebench Version 1.4.9.1
1022864: 0.000: Allocated 170MB of shared memory
1022864: 0.001: Creating/pre-allocating files and filesets
1022864: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
1022864: 0.033: Removed any existing fileset seqset in 1 seconds
1022864: 0.033: making tree for filset /mnt/nvme0n1p6/seqset
1022864: 0.033: Creating fileset seqset...
1022864: 5.817: Preallocated 1 of 1 of fileset seqset in 6 seconds
1022864: 5.817: waiting for fileset pre-allocation to finish
1022864: 5.817: Running 'sync'
1022864: 6.264: Running 'echo 3 > /proc/sys/vm/drop_caches'
1022864: 6.592: Attempting to create fileset more than once, ignoring
1023101: 6.592: Starting 1 rnd_writer instances
1023102: 6.594: Starting 1 seq_thread threads
1022864: 7.594: Running...
1022864: 52.598: Run took 45 seconds...
1022864: 52.599: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
wrand1               16384ops      364ops/s 364.1mb/s      2.7ms/op      602us/op-cpu [1ms - 23ms]
open1                1ops        0ops/s   0.0mb/s      1.5ms/op        0us/op-cpu [1ms - 1ms]
1022864: 52.599: IO Summary: 16386 ops, 364.101 ops/s, (0/364 r/w), 364.1mb/s,   6754us cpu/op,   2.7ms latency
1022864: 52.599: Shutting down processes


sudo filebench -f rnd-rd-1th-1f-1024KB.f 
Filebench Version 1.4.9.1
1027521: 0.000: Allocated 170MB of shared memory
1027521: 0.000: Creating/pre-allocating files and filesets
1027521: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
1027521: 0.028: Removed any existing fileset seqset in 1 seconds
1027521: 0.028: making tree for filset /mnt/nvme0n1p6/seqset
1027521: 0.029: Creating fileset seqset...
1027521: 6.108: Preallocated 1 of 1 of fileset seqset in 7 seconds
1027521: 6.108: waiting for fileset pre-allocation to finish
1027521: 6.108: Running 'sync'
1027521: 6.558: Running 'echo 3 > /proc/sys/vm/drop_caches'
1027521: 6.886: Attempting to create fileset more than once, ignoring
1027803: 6.887: Starting 1 rnd_reader instances
1027804: 6.890: Starting 1 seq_thread threads
1027521: 7.891: Running...
1027521: 14.892: Run took 7 seconds...
1027521: 14.892: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.2ms/op        0us/op-cpu [0ms - 0ms]
rrand1               16384ops     2340ops/s 2340.4mb/s      0.3ms/op      231us/op-cpu [0ms - 4ms]
open1                1ops        0ops/s   0.0mb/s      1.6ms/op        0us/op-cpu [1ms - 1ms]
1027521: 14.892: IO Summary: 16386 ops, 2340.657 ops/s, (2340/0 r/w), 2340.4mb/s,    695us cpu/op,   0.3ms latency
1027521: 14.892: Shutting down processes
