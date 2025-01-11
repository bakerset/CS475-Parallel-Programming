# Compiler settings
CC=g++
CFLAGS=--std=c++11 -g

# Default target to build the proj1 executable
all: proj4

# Target to compile Baker-Proj1.cpp into proj1 executable
proj4: Baker-Proj4.cpp
	$(CC) $(CFLAGS) Baker-Proj4.cpp -o proj4 -lm -fopenmp

# Target to execute the script for testing
run_tests: Baker-Proj4.bash
	bash Baker-Proj4.bash

# Clean rule to remove the proj1 executable
clean:
	rm -f proj4
