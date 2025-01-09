# Corrupted Blood Project: SEIR Model Simulations

## Overview
This folder contains refactored implementations of the SEIR (Susceptible-Exposed-Infected-Recovered) model for simulating disease spread. These simulations originated from the `6330` Parallel Processing course project and have been cleaned and prepared for integration into the Corrupted Blood project.

### Files Included
1. **Parallel Implementation (`seir_parallel.c`)**:
   - Uses MPI (Message Passing Interface) for distributed processing.
   - Simulates the SEIR model on a population grid using multiple processes.

2. **Serial Implementation (`seir_serial.cpp`)**:
   - A simpler version of the SEIR simulation using a single process.

## How to Use
### Parallel Implementation
#### Compile:
```bash
mpicc -o seir_parallel seir_parallel.c
```

#### Run:
```bash
mpiexec -n <number_of_processes> ./seir_parallel
```
Replace `<number_of_processes>` with the number of parallel processes you want to use.

### Serial Implementation
#### Compile:
```bash
g++ -o seir_serial seir_serial.cpp
```

#### Run:
```bash
./seir_serial
```

## Future Work
- **Translation to Python**: The SEIR logic will be translated into Python for better integration with the Corrupted Blood project, leveraging libraries like NumPy and Matplotlib.
- **Advanced Features**: Adding real-world parameter tuning and visualizations.
