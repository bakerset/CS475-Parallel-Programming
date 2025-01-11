#!/bin/bash

# Remove existing results.csv file if present
rm -f results.csv

# CSV header
echo "NUMTRIALS, BLOCKSIZE, MegaTrials/sec, Probability (%)" > results.csv

for t in 1024 4096 16384 65536 262144 1048576 2097152
do
        for b in 8 32 64 128 256
        do
            /usr/local/apps/cuda/cuda-10.1/bin/nvcc -DNUMTRIALS=$t -DBLOCKSIZE=$b -o proj5 proj5.cu
            
            # Run the compiled program and capture output
            output=$(./proj5)

            # Append formatted results to results.csv
            echo "$output" >> results.csv
        done
done