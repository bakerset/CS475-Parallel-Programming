#!/bin/bash

# Remove existing performance.csv file if present
rm -f performance.csv

# CSV header
echo "Processors, Elements, Mega-Autocorrelations/sec" > performance.csv

# Compile the MPI program
mpic++ proj7.cpp -o proj7 -lmpi -lm

# Define the number of processors to test
PROCS="1 2 4 6 8"

# Loop through different numbers of processors
for NPROC in $PROCS; do
    # Execute the MPI program with the current number of processors
    output=$(mpirun -np $NPROC ./proj7)

    # Save performance results to performance.csv
    if [ "$NPROC" == "1" ]; then
        echo "$NPROC, 8388608, $output" >> performance.csv
    fi
done

# Clean up the executable
rm -f proj7
