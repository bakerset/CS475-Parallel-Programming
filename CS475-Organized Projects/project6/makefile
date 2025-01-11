# Compiler settings
CC = g++
LDFLAGS = -lm -fopenmp
LIBS = /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1

# Default target to build the proj06 executable
all: proj06

proj06: proj06.cpp 
	$(CC) proj06.cpp -o proj06 $(LIBS) $(LDFLAGS)

run_tests: proj06.bash
	bash proj06.bash

# Clean rule to remove the proj5 executable and object files
clean:
	rm -f proj6