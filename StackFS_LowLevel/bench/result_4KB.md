### Ext4


sudo filebench -f seq-wr-1th-1f-4KB.f 
[sudo] password for leedaeeun: 
Filebench Version 1.4.9.1
930809: 0.000: Allocated 170MB of shared memory
930809: 0.001: Creating/pre-allocating files and filesets
930809: 0.001: File seqset: 61440.000MB
930809: 0.096: Removed any existing file seqset in 1 seconds
930809: 0.096: Creating file seqset...
930809: 0.096: Preallocated 0 of 1 of file seqset in 1 seconds
930809: 0.096: waiting for fileset pre-allocation to finish
930809: 0.096: Running 'sync'
930809: 0.101: Running 'echo 3 > /proc/sys/vm/drop_caches'
930809: 0.257: Attempting to create fileset more than once, ignoring
930825: 0.258: Starting 1 seq_writer instances
930826: 0.262: Starting 1 seq_thread threads
930809: 1.262: Running...
930809: 44.268: Run took 43 seconds...
930809: 44.268: Per-Operation Breakdown
fin                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
cl1                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
w1                   4194304ops    97531ops/s 381.0mb/s      0.0ms/op        5us/op-cpu [0ms - 21ms]
c1                   1ops        0ops/s   0.0mb/s      0.3ms/op        0us/op-cpu [0ms - 0ms]
930809: 44.268: IO Summary: 4194306 ops, 97530.707 ops/s, (0/97531 r/w), 381.0mb/s,     12us cpu/op,   0.0ms latency
930809: 44.268: Shutting down processes


sudo filebench -f seq-rd-1th-1f-4KB.f 
Filebench Version 1.4.9.1
933519: 0.000: Allocated 170MB of shared memory
933519: 0.000: Creating/pre-allocating files and filesets
933519: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
933519: 0.004: Removed any existing fileset seqset in 1 seconds
933519: 0.004: making tree for filset /mnt/nvme0n1p6/seqset
933519: 0.004: Creating fileset seqset...
933519: 0.558: Preallocated 1 of 1 of fileset seqset in 1 seconds
933519: 0.558: waiting for fileset pre-allocation to finish
933519: 0.558: Running 'sync'
933519: 1.081: Running 'echo 3 > /proc/sys/vm/drop_caches'
933519: 1.396: Attempting to create fileset more than once, ignoring
933565: 1.396: Starting 1 seq_reader instances
933566: 1.397: Starting 1 seq_thread threads
933519: 2.398: Running...
933519: 42.403: Run took 40 seconds...
933519: 42.404: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
read1                4194305ops   104844ops/s 409.5mb/s      0.0ms/op        5us/op-cpu [0ms - 0ms]
open1                1ops        0ops/s   0.0mb/s      0.1ms/op        0us/op-cpu [0ms - 0ms]
933519: 42.404: IO Summary: 4194307 ops, 104844.163 ops/s, (104844/0 r/w), 409.5mb/s,     11us cpu/op,   0.0ms latency
933519: 42.404: Shutting down processes


sudo filebench -f rnd-wr-1th-1f-4KB.f 
Filebench Version 1.4.9.1
936463: 0.000: Allocated 170MB of shared memory
936463: 0.000: Creating/pre-allocating files and filesets
936463: 0.000: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
936463: 0.003: Removed any existing fileset seqset in 1 seconds
936463: 0.003: making tree for filset /mnt/nvme0n1p6/seqset
936463: 0.003: Creating fileset seqset...
936463: 0.552: Preallocated 1 of 1 of fileset seqset in 1 seconds
936463: 0.552: waiting for fileset pre-allocation to finish
936463: 0.552: Running 'sync'
936463: 1.060: Running 'echo 3 > /proc/sys/vm/drop_caches'
936463: 1.304: Attempting to create fileset more than once, ignoring
936506: 1.305: Starting 1 rnd_writer instances
936507: 1.308: Starting 1 seq_thread threads
936463: 2.309: Running...
936463: 45.314: Run took 43 seconds...
936463: 45.314: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
wrand1               4194304ops    97531ops/s 381.0mb/s      0.0ms/op        5us/op-cpu [0ms - 0ms]
open1                1ops        0ops/s   0.0mb/s      0.2ms/op        0us/op-cpu [0ms - 0ms]
936463: 45.314: IO Summary: 4194306 ops, 97531.013 ops/s, (0/97531 r/w), 381.0mb/s,     12us cpu/op,   0.0ms latency
936463: 45.314: Shutting down processes


sudo filebench -f rnd-rd-1th-1f-4KB.f 
Filebench Version 1.4.9.1
939670: 0.000: Allocated 170MB of shared memory
939670: 0.000: Creating/pre-allocating files and filesets
939670: 0.000: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
939670: 0.004: Removed any existing fileset seqset in 1 seconds
939670: 0.004: making tree for filset /mnt/nvme0n1p6/seqset
939670: 0.004: Creating fileset seqset...
939670: 0.577: Preallocated 1 of 1 of fileset seqset in 1 seconds
939670: 0.577: waiting for fileset pre-allocation to finish
939670: 0.577: Running 'sync'
939670: 1.061: Running 'echo 3 > /proc/sys/vm/drop_caches'
939670: 1.289: Attempting to create fileset more than once, ignoring
939716: 1.289: Starting 1 rnd_reader instances
939717: 1.292: Starting 1 seq_thread threads
939670: 2.292: Running...
939670: 68.298: Run took 66 seconds...
939670: 68.299: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
rrand1               4194304ops    63544ops/s 248.2mb/s      0.0ms/op        6us/op-cpu [0ms - 3ms]
open1                1ops        0ops/s   0.0mb/s      0.2ms/op        0us/op-cpu [0ms - 0ms]
939670: 68.299: IO Summary: 4194306 ops, 63544.340 ops/s, (63544/0 r/w), 248.2mb/s,     14us cpu/op,   0.0ms latency
939670: 68.299: Shutting down processes




### StackfsBase


sudo filebench -f seq-wr-1th-1f-4KB.f
Filebench Version 1.4.9.1
947638: 0.000: Allocated 170MB of shared memory
947638: 0.001: Creating/pre-allocating files and filesets
947638: 0.002: File seqset: 61440.000MB
947638: 0.008: Removed any existing file seqset in 1 seconds
947638: 0.008: Creating file seqset...
947638: 0.008: Preallocated 0 of 1 of file seqset in 1 seconds
947638: 0.008: waiting for fileset pre-allocation to finish
947638: 0.008: Running 'sync'
947638: 0.016: Running 'echo 3 > /proc/sys/vm/drop_caches'
947638: 0.213: Attempting to create fileset more than once, ignoring
947643: 0.213: Starting 1 seq_writer instances
947644: 0.217: Starting 1 seq_thread threads
947638: 1.217: Running...
947638: 102.226: Run took 101 seconds...
947638: 102.226: Per-Operation Breakdown
fin                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
cl1                  1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
w1                   4194304ops    41524ops/s 162.2mb/s      0.0ms/op        9us/op-cpu [0ms - 16ms]
c1                   1ops        0ops/s   0.0mb/s      2.1ms/op        0us/op-cpu [2ms - 2ms]
947638: 102.227: IO Summary: 4194306 ops, 41524.221 ops/s, (0/41524 r/w), 162.2mb/s,     50us cpu/op,   0.0ms latency
947638: 102.227: Shutting down processes


sudo filebench -f seq-rd-1th-1f-4KB.f 
Filebench Version 1.4.9.1
954536: 0.000: Allocated 170MB of shared memory
954536: 0.001: Creating/pre-allocating files and filesets
954536: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
954536: 0.160: Removed any existing fileset seqset in 1 seconds
954536: 0.160: making tree for filset /mnt/nvme0n1p6/seqset
954536: 0.161: Creating fileset seqset...
954536: 6.249: Preallocated 1 of 1 of fileset seqset in 7 seconds
954536: 6.249: waiting for fileset pre-allocation to finish
954536: 6.249: Running 'sync'
954536: 6.670: Running 'echo 3 > /proc/sys/vm/drop_caches'
954536: 7.085: Attempting to create fileset more than once, ignoring
954810: 7.085: Starting 1 seq_reader instances
954811: 7.090: Starting 1 seq_thread threads
954536: 8.090: Running...
954536: 48.094: Run took 40 seconds...
954536: 48.095: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.3ms/op        0us/op-cpu [0ms - 0ms]
read1                4194305ops   104847ops/s 409.5mb/s      0.0ms/op        5us/op-cpu [0ms - 0ms]
open1                1ops        0ops/s   0.0mb/s      1.7ms/op        0us/op-cpu [1ms - 1ms]
954536: 48.095: IO Summary: 4194307 ops, 104846.965 ops/s, (104847/0 r/w), 409.5mb/s,     12us cpu/op,   0.0ms latency
954536: 48.095: Shutting down processes


sudo filebench -f rnd-wr-1th-1f-4KB.f 
Filebench Version 1.4.9.1
959114: 0.000: Allocated 170MB of shared memory
959114: 0.001: Creating/pre-allocating files and filesets
959114: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
959114: 0.026: Removed any existing fileset seqset in 1 seconds
959114: 0.026: making tree for filset /mnt/nvme0n1p6/seqset
959114: 0.027: Creating fileset seqset...
959114: 5.843: Preallocated 1 of 1 of fileset seqset in 6 seconds
959114: 5.843: waiting for fileset pre-allocation to finish
959114: 5.843: Running 'sync'
959114: 6.299: Running 'echo 3 > /proc/sys/vm/drop_caches'
959114: 6.647: Attempting to create fileset more than once, ignoring
959348: 6.648: Starting 1 rnd_writer instances
959349: 6.652: Starting 1 seq_thread threads
959114: 7.652: Running...
959114: 112.660: Run took 105 seconds...
959114: 112.660: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
wrand1               4194304ops    39943ops/s 156.0mb/s      0.0ms/op        9us/op-cpu [0ms - 1ms]
open1                1ops        0ops/s   0.0mb/s      2.5ms/op        0us/op-cpu [2ms - 2ms]
959114: 112.660: IO Summary: 4194306 ops, 39942.928 ops/s, (0/39943 r/w), 156.0mb/s,     54us cpu/op,   0.0ms latency
959114: 112.660: Shutting down processes


sudo filebench -f rnd-rd-1th-1f-4KB.f 
Filebench Version 1.4.9.1
964839: 0.000: Allocated 170MB of shared memory
964839: 0.000: Creating/pre-allocating files and filesets
964839: 0.001: Fileset seqset: 1 files, 0 leafdirs, avg dir width = 1, avg dir depth = -nan, 2096.641MB
964839: 0.029: Removed any existing fileset seqset in 1 seconds
964839: 0.029: making tree for filset /mnt/nvme0n1p6/seqset
964839: 0.030: Creating fileset seqset...
964839: 5.887: Preallocated 1 of 1 of fileset seqset in 6 seconds
964839: 5.887: waiting for fileset pre-allocation to finish
964839: 5.887: Running 'sync'
964839: 6.347: Running 'echo 3 > /proc/sys/vm/drop_caches'
964839: 6.789: Attempting to create fileset more than once, ignoring
965111: 6.789: Starting 1 rnd_reader instances
965112: 6.793: Starting 1 seq_thread threads
964839: 7.793: Running...
964839: 92.801: Run took 85 seconds...
964839: 92.802: Per-Operation Breakdown
finish               1ops        0ops/s   0.0mb/s      0.0ms/op        0us/op-cpu [0ms - 0ms]
close1               1ops        0ops/s   0.0mb/s      0.1ms/op        0us/op-cpu [0ms - 0ms]
rrand1               4194304ops    49340ops/s 192.7mb/s      0.0ms/op        7us/op-cpu [0ms - 1ms]
open1                1ops        0ops/s   0.0mb/s      2.5ms/op        0us/op-cpu [2ms - 2ms]
964839: 92.802: IO Summary: 4194306 ops, 49339.975 ops/s, (49340/0 r/w), 192.7mb/s,     30us cpu/op,   0.0ms latency
964839: 92.802: Shutting down processes
