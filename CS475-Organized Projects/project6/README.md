# OpenCL Parallel Linear Regression

This project uses OpenCL to compute the partial sums needed for linear regression over a large dataset. The host C++ program loads input data, runs an OpenCL kernel to generate per-element terms, and solves for the regression slope and intercept.

## Highlights

- Demonstrates OpenCL platform/device setup and kernel dispatch.
- Computes regression terms in parallel on an OpenCL device.
- Separates host orchestration in C++ from device work in `.cl` kernel code.
- Benchmarks throughput across OpenCL local work sizes.

## Key Files

- `proj06.cpp` - Host-side OpenCL setup, data loading, kernel execution, and regression solve.
- `proj06.cl` - OpenCL kernel for computing regression partial terms.
- `proj06.bash` - Benchmark runner.
- `makefile` - Builds the `proj06` executable.
- `cl.h` and `cl_platform.h` - OpenCL headers included with the project.

## Build

```bash
make
```

Requires OpenCL runtime libraries and the `p6.data` input file.
