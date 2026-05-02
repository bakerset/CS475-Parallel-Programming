# OpenMP K-Means City Clustering

This project clusters U.S. cities into a configurable number of capital regions using an iterative k-means style algorithm. OpenMP parallelizes the city-to-capital assignment phase and records performance across different numbers of threads and capitals.

## Highlights

- Implements iterative nearest-center clustering over geographic coordinates.
- Uses OpenMP to parallelize distance calculations and assignment work.
- Tracks convergence with repeated capital recomputation.
- Records timing and speedup data to `results.csv`.

## Key Files

- `Baker-proj3.cpp` - Main OpenMP clustering implementation.
- `UsCities.data` - City longitude/latitude input data.
- `Baker-proj3.bash` - Benchmark runner.
- `makefile` - Builds the `proj3` executable.
- `results.csv` - Example performance results.

## Build

```bash
make
```

## Run Benchmarks

```bash
make run_tests
```
