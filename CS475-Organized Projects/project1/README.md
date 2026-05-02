# OpenMP Monte Carlo Golf Ball Simulation

This project estimates the probability that a golf ball clears a gap using a Monte Carlo simulation parallelized with OpenMP. Randomized launch and landing parameters are evaluated across many trials, then benchmarked across different thread counts and trial sizes.

## Highlights

- Uses OpenMP to parallelize independent Monte Carlo trials.
- Measures probability of success and throughput in mega-trials per second.
- Automates performance sweeps with `Baker-Proj1.bash`.
- Exports benchmark results to `results.csv`.

## Key Files

- `Baker-Proj1.cpp` - Main OpenMP Monte Carlo simulation.
- `Baker-Proj1.bash` - Batch runner for thread/trial performance experiments.
- `makefile` - Builds the `proj1` executable.
- `results.csv` - Example benchmark output.

## Build

```bash
make
```

## Run Benchmarks

```bash
make run_tests
```
