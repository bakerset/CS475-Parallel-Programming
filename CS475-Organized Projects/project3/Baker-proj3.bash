#!/bin/bash

# Remove existing results.csv file if present
rm -f results.csv

for t in 1 2 4 6 8
do
  for n in 2 3 4 5 10 15 20 30 40 50
  do
    # Compile Baker-proj3.cpp with the specified NUMT and NUMTRIALS
    g++ Baker-proj3.cpp -DNUMT=$t -DNUMCAPITALS=$n -o proj3 -lm -fopenmp

    # Run the compiled program and capture output
    output=$(./proj3)

    # Extract the desired fields from the output
    result=$(echo "$output" | grep -oE "^$t ,  $n , [0-9]+ , [0-9]+\.[0-9]+:")

    echo "$result" >> results.csv 
  done
done