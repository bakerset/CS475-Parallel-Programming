# Compiler settings
CC=g++
CFLAGS=--std=c++11 -g

# Default target to build the proj2 executable
all: proj2

# Target to compile baker-proj2.cpp into proj2 executable
proj2: baker-proj2.cpp
	$(CC) $(CFLAGS) baker-proj2.cpp -o proj2 -lm -fopenmp

# Clean rule to remove the proj2 executable
clean:
	rm -f proj2
