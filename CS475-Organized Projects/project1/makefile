# Compiler settings
CC=g++
CFLAGS=--std=c++11 -g

# Default target to build the proj1 executable
all: proj1

# Target to compile Baker-Proj1.cpp into proj1 executable
proj1: Baker-Proj1.cpp
	$(CC) $(CFLAGS) Baker-Proj1.cpp -o proj1 -lm -fopenmp

# Target to execute the script for testing
run_tests: Baker-Proj1.bash
	bash Baker-Proj1.bash

# Clean rule to remove the proj1 executable
clean:
	rm -f proj1
