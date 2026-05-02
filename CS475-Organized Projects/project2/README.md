# OpenMP Ecosystem Simulation with Custom Barriers

This project models a small ecosystem over time using OpenMP sections and a custom barrier implementation. Independent agents update grain height, deer population, predator population, temperature, and precipitation while synchronizing at monthly time steps.

## Highlights

- Demonstrates thread coordination with explicit barrier logic.
- Simulates interacting environmental and population variables.
- Uses randomized weather effects to influence growth and population changes.
- Shows a multi-agent OpenMP pattern where each thread owns part of the model.

## Key Files

- `baker-proj2.cpp` - Main ecosystem simulation.
- `makefile` - Builds the `proj2` executable.

## Build

```bash
make
```
