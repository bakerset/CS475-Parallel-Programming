#!/bin/bash

# Remove existing results.csv file if present
rm -f results.csv

# CSV header
echo "ARRAYSIZE,SSETime,SSEPerformance,CPPTime,CPPPerformance" > results.csv

for t in 100
do
  for n in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8000000
  do
    # Compile Baker-Proj4.cpp with the specified ARRAYSIZES and NUMTRIES
    g++ Baker-Proj4.cpp -DNUMTRIES=$t -DARRAYSIZE=$n -o proj4 -lm -fopenmp

    # Run the compiled program and capture output
    output=$(./proj4)

    # Append formatted results to results.csv
    echo "$output" >> results.csv
  done
done
