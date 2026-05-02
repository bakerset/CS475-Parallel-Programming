# MPI Distributed Signal Autocorrelation

This project computes autocorrelation sums for a large signal using MPI. The signal is partitioned across processes, each process computes local autocorrelation work, and the results are gathered to reveal periodic structure in the data.

## Highlights

- Uses MPI for distributed-memory parallel processing.
- Splits a large signal across multiple processes.
- Computes autocorrelation values for many shifts.
- Produces plot/performance data for analyzing hidden signal patterns.

## Key Files

- `proj7.cpp` - Main MPI autocorrelation implementation.
- `proj7.bash` - Benchmark runner using `mpirun`.
- `makefile` - Builds the `proj7` executable.

## Build

```bash
make
```

Requires an MPI compiler/runtime such as `mpic++` and `mpirun`, plus the large signal input file.
