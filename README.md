# Parallel-Merge-Sort
Attempt to benchmark Parallel Merge Sorts.  Contains serial merge sort, openmp, and pthread

# Goal
Create three seperate Merge Sorts and a testing framework to diplay differences in performance accross different CPU, RAM, and memory contrants.

# Steps to Compile and Run
This repo is designed for ease of use and code repeatablility across each Merge Sort. Follow the below instructions to compile and execute code.

1. Edit definitions.h to utilize array size (var MAX) and cores (var numThreads) desired for test.
2. Run 'make all' to compile all targets
3. Run './numGen [size]' to create txt file of size N randomly generated numbers seperated by a space.
4. Run './mergeSort' to view test results for serial merge sort utilizing specified array size and threads.
5. Run './pthread' to view test results for pthreaded merge sort utilizing specified array size and threads.
6. Run './openmp' to view test results for openmp merge sort utilizing specified array size and threads.
7. 'make clean' to clean up directory.
