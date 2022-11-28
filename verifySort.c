/*
 * Grant Lubeck 20221126
 * This file is used to validate the various mergeSorts correctly sorted the arrays.
 * Rest of mergeSort timing code can be found at gplubeck github
 */
#include <stdbool.h>
#include <stdio.h>
#include "verifySort.h"

bool verifySort(int* array, int size){
    for(int i = 0; i < size -1; i++){
        if(array[i] > array[i+1]){
            fprintf(stdout, "Failed Sort. Element %d:%d is larger than element %d:%d.\n", i, array[i], i+1, array[i+1]);
            return false;
        }
    }
    return true;
}

void printArray(int* array, int size){
    int i;
    for(i=0; i < size; i++)
        fprintf(stdout,"%d ", array[i]);
}
