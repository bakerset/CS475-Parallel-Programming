# Compiler settings
CC = g++
LDFLAGS = -lm
LIBS = -lmpi

# Default target to build the proj7 executable
all: proj7

proj7: proj7.cpp
	$(CC) proj7.cpp -o proj7 $(LIBS) $(LDFLAGS)

run_tests: proj7.bash
	bash proj7.bash

# Clean rule to remove the proj7 executable
clean:
	rm -f proj7
