#!/bin/bash

# Remove existing results.csv file if present
rm -f results.csv

# CSV header
echo "NUMT,NUMTRIALS,Probability (%),MegaTrials/sec" > results.csv

for t in 1 2 4 6 8
do
  for n in 1 10 100 1000 10000 100000 500000 1000000
  do
    # Compile Baker-Proj1.cpp with the specified NUMT and NUMTRIALS
    g++ Baker-Proj1.cpp -DNUMT=$t -DNUMTRIALS=$n -o proj1 -lm -fopenmp

    # Run the compiled program and capture output
    output=$(./proj1)

    # Append formatted results to results.csv
    echo "$output" >> results.csv
  done
done
