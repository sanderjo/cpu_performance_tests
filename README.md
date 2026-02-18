# cpu_performance_tests

# oringal drystone ... probably single-core

```
$ sh dry.c

...

Dhrystone Benchmark, Version C, Version 2.2a
Program compiled without 'register' attribute
Using times(), HZ=100

Trying 50000 runs: too few
Trying 500000 runs: too few
Trying 5000000 runs: too few
Trying 50000000 runs: 
Microseconds for one run through Dhrystone:       0.07 
Dhrystones per Second:                        14005602 
```

# Single and Multi core

```
$ ./perf_multi 
System detected: 8 CPU cores

Running Single-Core Test (0.2s)...
Single-Core Score: 23.45 Million Ops/sec

Running Multi-Core Test on 8 cores (0.2s)...
Multi-Core Total Score: 224.39 Million Ops/sec
Multi-Core Speedup: 9.57x faster than single core
```
