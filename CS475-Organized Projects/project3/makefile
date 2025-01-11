# Compiler settings
CC=g++
CFLAGS=--std=c++11 -g

# Default target to build the proj2 executable
all: proj3

# Target to compile baker-proj2.cpp into proj2 executable
proj3: Baker-proj3.cpp
	$(CC) $(CFLAGS) Baker-proj3.cpp -o proj3 -lm -fopenmp

run_tests: Baker-proj3.bash
	bash Baker-proj3.bash

# Clean rule to remove the proj2 executable
clean:
	rm -f proj3
