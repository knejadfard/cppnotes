# Profiling

## Callgrind
In order to run the callgrind tool, run the following command:
```
valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes <path to binary>
```

Once the program run is finished, a new file with name `callgrind.out.<pid>` will be created. This file contains profiling information and can be viewed with KCachegrind.
