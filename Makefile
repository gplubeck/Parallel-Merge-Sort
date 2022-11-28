CC=gcc
CFLAGS=-I.

all: clean mergeSort openmp pthread numberGen

mergeSort: mergeSort.o verifySort.o definitions.h clock.o
	$(CC) -o mergeSort mergeSort.o verifySort.o clock.o

openmp: openmp_mergeSort.o definitions.h verifySort.o clock.o
	$(CC) -o openmp -fopenmp openmp_mergeSort.c verifySort.o clock.o

pthread: pthread_mergeSort.o definitions.h verifySort.o clock.o
	$(CC) -o pthread pthread_mergeSort.o verifySort.o clock.o

numberGen: numberGen.o definitions.h
	$(CC) -o numberGen numberGen.o

clean:
	rm -f mergeSort mergeSort.o openmp openmp_mergeSort.o numberGen numberGen.o pthread pthread_mergeSort.o verifySort.o clock.o rand.txt
	
