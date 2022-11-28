/*
 * 20221125 Grant Lubeck
 * Comparing Parallelism for PThreads vs OpenMP
 * This code is thei pthread Merge Sort used in the comparision
 * This code expects to take in random numbers seperated by a space from a file in the local directory called rand.txt
 * Must have MAX defined in Makefile
 * Rest of code in this project can be found at: 
 * 
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "verifySort.h"
#include "definitions.h"
#include "clock.h"

//global array
int *a;

// thread control parameters
struct tsk {
    int tsk_no;
    int tsk_low;
    int tsk_high;
};

// merge function for merging two parts
void merge(int low, int mid, int high){

    // n1 is size of left part and n2 is size of right part
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    int i;
    int j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = a[i + low];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];

    int k = low;

    i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1)
        a[k++] = left[i++];

    // insert remaining values from right
    while (j < n2)
        a[k++] = right[j++];

    free(left);
    free(right);
}

// merge sort function
void merge_sort(int low, int high){

    // calculating mid point of array
    int mid = low + (high - low) / 2;

    if (low < high) {
        //first half
        merge_sort(low, mid);

        //second half
        merge_sort(mid + 1, high);

        // merging the two halves
        merge(low, mid, high);
    }
}

// thread function for multi-threading
void * thread_merge_sort(void *arg){
    struct tsk *tsk = arg;
    int low;
    int high;

    // calculating low and high
    low = tsk->tsk_low;
    high = tsk->tsk_high;

    // evaluating mid point
    int mid = low + (high - low) / 2;

    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }

    return 0;
}

int main(int argc, char **argv){
    int i;
    char *cp;
    struct tsk *tsk;
    struct timespec start, end, sortTime;

    // allocate the array
    a = malloc(sizeof(int) * MAX);
    if( a == NULL){
        fprintf(stdout, "Failed Memory Allocation.");
        exit(1);
    }

    //read in array
    FILE *fp;
    if((fp=fopen("rand.txt", "r")) == NULL){
        fprintf(stdout, "Could not read from rand.txt.");
        exit(1);
    }

    for(i=0; i<=MAX; i++)
        fscanf(fp, "%d", &a[i]);
   

    pthread_t threads[numThreads];
    struct tsk tsklist[numThreads];

    int len = MAX / numThreads;

    int low = 0;

    for (int i = 0; i < numThreads; i++, low += len) {
        tsk = &tsklist[i];
        tsk->tsk_no = i;
        
        tsk->tsk_low = low;
        tsk->tsk_high = low + len - 1;
        if (i == (numThreads - 1))
            tsk->tsk_high = MAX - 1;
    }

    //start timer
    clock_gettime(CLOCK_REALTIME, &start);

    // creating 4 threads
    for (int i = 0; i < numThreads; i++) {
        tsk = &tsklist[i];
        pthread_create(&threads[i], NULL, thread_merge_sort, tsk);
    }

    //joining all 4 threads
    for (int i = 0; i < numThreads; i++)
        pthread_join(threads[i], NULL);

    // merging the final 4 parts
    struct tsk *tskm = &tsklist[0];
    for (int i = 1; i < numThreads; i++) {
        struct tsk *tsk = &tsklist[i];
        merge(tskm->tsk_low, tsk->tsk_low - 1, tsk->tsk_high);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    getTimeDelta(start, end, &sortTime);
    //sortTime = ((double) (end-start))/CLOCKS_PER_SEC;

    //validate correct sorting
    assert(1==verifySort(a, MAX-1));

    fprintf(stdout,"Utilizing %d cores pthead merge sort took %d.%.9ld seconds to sort %d elements.\n", numThreads, (int)sortTime.tv_sec, sortTime.tv_nsec, MAX);

    return 0;
}
