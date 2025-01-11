# Compiler settings
CUDA_PATH = /usr/local/apps/cuda/cuda-10.1
CUDA_BIN_PATH = $(CUDA_PATH)/bin
CUDA_NVCC = $(CUDA_BIN_PATH)/nvcc

# Default target to build the proj5 executable
all: proj5

# Target to compile proj5.cu into proj5 executable
proj5: proj5.cu
	$(CUDA_NVCC) proj5.cu -o proj5

# Target to execute the script for testing
run_tests: proj5.bash
	bash proj5.bash

# Clean rule to remove the proj5 executable and object files
clean:
	rm -f proj5
