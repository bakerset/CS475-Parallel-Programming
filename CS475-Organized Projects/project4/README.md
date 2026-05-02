# SIMD Vector Math Benchmark

This project compares scalar C++ vector math with hand-written SSE SIMD routines. It benchmarks vector multiplication and multiply-reduction workloads across array sizes to show how data-level parallelism affects throughput.

## Highlights

- Implements scalar and SIMD versions of array multiplication.
- Uses SSE-width operations for vectorized floating-point math.
- Benchmarks multiplication and multiplication-plus-sum reductions.
- Writes comparative performance data to `results.csv`.

## Key Files

- `Baker-Proj4.cpp` - SIMD and scalar benchmark implementation.
- `Baker-Proj4.bash` - Benchmark runner for multiple array sizes.
- `convert.py` - Output conversion helper.
- `makefile` - Builds the `proj4` executable.
- `results.csv` - Example benchmark results.

## Build

```bash
make
```

## Run Benchmarks

```bash
make run_tests
```
