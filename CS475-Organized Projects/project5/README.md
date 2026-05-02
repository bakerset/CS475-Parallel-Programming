# CUDA Monte Carlo Golf Ball Simulation

This project ports the Monte Carlo golf ball probability simulation to CUDA. It launches GPU kernels to evaluate many randomized trials in parallel, then compares probability and throughput behavior against CPU-oriented approaches.

## Highlights

- Uses CUDA kernels for massively parallel Monte Carlo trial evaluation.
- Manages host/device arrays for randomized simulation inputs and success flags.
- Reports probability of success and GPU throughput.
- Includes NVIDIA helper headers used by the CUDA sample-style workflow.

## Key Files

- `proj5.cu` - Main CUDA simulation source.
- `proj5.bash` - Benchmark runner.
- `makefile` - Builds the `proj5` executable with `nvcc`.
- `helper_*.h` and `exception.h` - CUDA helper headers.
- `results.csv` - Example benchmark results.

## Build

```bash
make
```

Requires CUDA and `nvcc`.
