# Profiling

## Linux perf
There is a Linux tool named `perf` that can provide profiling information.

The following command allows for recording information that may shed light on how a program is performing in general:
```
perf stat -e task-clock,cycles,instructions,cache-references,cache-misses <path to binary>
```

The following is the output from one of my tests:
```
 Performance counter stats for 'build/cache/cache':

            165.07 msec task-clock                #    0.991 CPUs utilized
       419,512,046      cycles                    #    2.541 GHz
       715,494,283      instructions              #    1.71  insn per cycle
            37,407      cache-references          #    0.227 M/sec
            13,511      cache-misses              #   36.119 % of all cache refs

       0.166623847 seconds time elapsed

       0.166557000 seconds user
       0.000000000 seconds sys
```

Based on this output, the program ran for a total of 419,512,046 CPU cycles and executed 715,494,283 instructions. This gives an average of 1.71 instructions per cycle. There were a total of 13,511 cache misses, which is around 36% of all cache references.

If there is a need to dig in further into cache misses, `perf record` should be used to take samples and record them in a file for analysis:
```
perf record -e cache-misses <path to binary>
```

The above command results in the creation of a file named `perf.data`. A report can be generated from this file by executing:
```
perf report --stdio
```

The output looks like the following:
```
# To display the perf.data header info, please use --header/--header-only options.
#
#
# Total Lost Samples: 0
#
# Samples: 17  of event 'cache-misses'
# Event count (approx.): 15308
#
# Overhead  Command  Shared Object      Symbol
# ........  .......  .................  ............................
#
    22.43%  cache    ld-2.31.so         [.] _dl_lookup_symbol_x
    14.80%  cache    [kernel.kallsyms]  [k] __mod_memcg_lruvec_state
    12.97%  cache    [kernel.kallsyms]  [k] PageHuge
    12.52%  cache    [kernel.kallsyms]  [k] memcg_slab_free_hook
    11.95%  cache    libm-2.31.so       [.] __cosf_ifunc
    10.35%  cache    ld-2.31.so         [.] do_lookup_x
     5.57%  cache    [kernel.kallsyms]  [k] perf_event_mmap
     4.79%  cache    [kernel.kallsyms]  [k] rcu_sched_clock_irq
     2.63%  cache    [kernel.kallsyms]  [k] page_add_file_rmap
     1.06%  perf_5.  [kernel.kallsyms]  [k] perf_iterate_sb
     0.44%  cache    ld-2.31.so         [.] _dl_fini
     0.44%  cache    libc-2.31.so       [.] cfree@GLIBC_2.2.5
     0.03%  perf_5.  [kernel.kallsyms]  [k] perf_event_comm
     0.01%  perf_5.  [kernel.kallsyms]  [k] strrchr


#
# (Tip: To record every process run by a user: perf record -u <user>)
#
```

Reference: https://developers.redhat.com/blog/2014/03/10/determining-whether-an-application-has-poor-cache-performance-2/

## Callgrind
In order to run the callgrind tool, run the following command:
```
valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes <path to binary>
```

Once the program run is finished, a new file with name `callgrind.out.<pid>` will be created. This file contains profiling information and can be viewed with KCachegrind.
