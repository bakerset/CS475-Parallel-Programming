# Compiler settings
CC=g++
CFLAGS=--std=c++11 -g

# Default target to build the proj2 executable
all: proje2

# Target to compile baker-proj2.cpp into proj2 executable
proje2: baker-proj2copy.cpp
	$(CC) $(CFLAGS) baker-proj2copy.cpp -o proje2 -lm -fopenmp

# Clean rule to remove the proj2 executable
clean:
	rm -f proje2
