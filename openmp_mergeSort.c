/*
 * 20221125
 * Grant Lubeck Comparing Parallelism for PThreads vs OpenMP
 * This code is the Open MP Merge Sort for testing.
 * This code expects to take in random numbers seperated by a space from a file in the local directory called rand.txt
 * Must have MAX and numThreads defined in Makefile
 
 * NOTE: THIS CODE DOES NOT SCALE WELL.  Please view benchmarking results.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <omp.h>

#include "verifySort.h" //contains functions to print arrays or verify it is all in numerical order
#include "definitions.h" //defines MAX and numThreads
#include "clock.h" //contains function to get execution speeds 


int merge(int a[],int b[], int low, int high, int mid){
    int i, j, k;
    i=low; j=mid+1; k=low;

    while((i<=mid)&&(j<=high)){
        if(a[i]<a[j]){
            b[k]=a[i]; k++; i++;
        } else {
            b[k]=a[j]; k++; j++;
        }
    }
    while(i<=mid){
        b[k]=a[i]; k++; i++;
    }
    while(j<=high){
        b[k]=a[j]; k++; j++;
    }
    for(i=low;i<k;i++) {
        a[i]=b[i];
    }
}

int mergesort(int a[],int b[] , int low, int high) {
    int mid;
    
    if(low<high) {
        //find midpoint
        mid=(low+high)/2;  

        //sort first half
        #pragma omp task
        mergesort(a, b, low, mid);
        
        //sort second half
        #pragma omp task
        mergesort(a, b, mid+1, high); 

        //merge after all tasks are complete
        #pragma omp taskwait
        merge(a, b, low, high, mid); 

    }
}



int main(int argc, char **argv) {
    
    int i, *a, *b;
    a =(int *)malloc(sizeof(int)*MAX);
    b =(int *)malloc(sizeof(int)*MAX);
    
    if(a == NULL || b == NULL){
        fprintf(stdout, "Failed Memory Allocation."); 
        exit(1);
    }

    struct timespec start, end, sortTime;
    FILE *fp;
    if((fp=fopen("rand.txt", "r")) == NULL){
       fprintf(stdout, "Could not read from rand.txt.");
       exit(1);
    }

    for(i=0; i<=MAX; i++)
       fscanf(fp, "%d", &a[i]);

     //start timer
    clock_gettime(CLOCK_REALTIME, &start);
    omp_set_dynamic(1);
    omp_set_num_threads(numThreads);
    #pragma omp parallel
    {
    #pragma omp master
    mergesort(a, b, 0, (MAX-1));
    }
    clock_gettime(CLOCK_REALTIME, &end);
    getTimeDelta(start, end, &sortTime);
   
   //validate correct sorting
   assert(1==verifySort(a, MAX-1));

   fprintf(stdout,"Utilizing %d cores OpenMP Merge Sort took %d.%.9ld seconds to sort %d elements.\n", numThreads, (int)sortTime.tv_sec, sortTime.tv_nsec, MAX);

    return 0;
}
