# CS475 Parallel Programming Portfolio

This repository collects seven CS475 projects focused on high-performance and parallel programming in C, C++, CUDA, OpenCL, OpenMP, SIMD, and MPI. Each folder has been given a portfolio-facing title and summary so reviewers can quickly understand the problem, implementation approach, and technical skills demonstrated.

## Projects

| Folder | Portfolio title | What it demonstrates |
| --- | --- | --- |
| `project1` | OpenMP Monte Carlo Golf Ball Simulation | Parallel Monte Carlo trials, probability estimation, OpenMP scaling, CSV performance reporting |
| `project2` | OpenMP Ecosystem Simulation with Custom Barriers | Multi-agent monthly simulation, thread coordination, weather modeling, predator-prey dynamics |
| `project2copy` | Ecosystem Simulation Data Export Variant | Extended project 2 output pipeline with formatted simulation data and CSV conversion |
| `project3` | OpenMP K-Means City Clustering | Iterative clustering, parallel nearest-capital assignment, convergence tracking, performance measurement |
| `project4` | SIMD Vector Math Benchmark | SSE assembly routines, scalar vs SIMD comparison, array multiplication and reduction benchmarks |
| `project5` | CUDA Monte Carlo Golf Ball Simulation | GPU kernels, CUDA memory management, host/device probability simulation, throughput analysis |
| `project6` | OpenCL Parallel Linear Regression | OpenCL kernel execution, GPU data reduction setup, linear regression over large data files |
| `project7` | MPI Distributed Signal Autocorrelation | Distributed-memory processing, signal analysis, MPI scatter/gather style coordination, performance reporting |

## Portfolio Notes

- The folders preserve their original course project layout so the source, scripts, and makefiles stay easy to compare with the submitted work.
- Generated binaries, temporary logs, and large generated datasets are ignored by git. Recreate them with each project's makefile or script when needed.
- Result CSV files are useful as examples of measured output, but fresh benchmark results should be regenerated on the target machine.

## Common Build Pattern

Most projects build with:

```bash
make
```

Projects that depend on CUDA, OpenCL, or MPI require the matching toolchain and runtime libraries installed on the machine where they are built.
