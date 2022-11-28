/*
 * 20221124
 * Grant Lubeck Comparing Parallelism for PThreads vs OpenMP
 * This code is the Merge Sort used as baseline for determining time of unparallelized code
 * This code expects to take in random numbers seperated by a space from a file in the local directory called rand.txt
 * Must have MAX defined in Makefile

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "verifySort.h"
#include "definitions.h" //defines MAX
#include "clock.h"

int a[MAX];
int b[MAX-1];

void merging(int low, int mid, int high) {
   int l1, l2, i;

   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(a[l1] <= a[l2])
         b[i] = a[l1++];
      else
         b[i] = a[l2++];
   }
   
   while(l1 <= mid)    
      b[i++] = a[l1++];

   while(l2 <= high)   
      b[i++] = a[l2++];

   for(i = low; i <= high; i++)
      a[i] = b[i];
}

void sort(int low, int high) {
   int mid;
   
   if(low < high) {
      mid = (low + high) / 2;
      sort(low, mid);
      sort(mid+1, high);
      merging(low, mid, high);
   } else { 
      return;
   }   
}

int main(int argc, char *args[]) { 
   int i;
   struct timespec start, end, sortTime;
   FILE *fp;
   if((fp=fopen("rand.txt", "r")) == NULL){
       fprintf(stdout, "Could not read from rand.txt.");
       exit(-1);
   }

   for(i=0; i<=MAX; i++){
       fscanf(fp, "%d", &a[i]);
   }


   //start timer
   clock_gettime(CLOCK_REALTIME, &start);
   sort(0, MAX);
   clock_gettime(CLOCK_REALTIME, &end);
   getTimeDelta(start, end, &sortTime);
   
   //validate correct sorting
   assert(1==verifySort(a, MAX-1));

   fprintf(stdout,"Merge Sort took %d.%.9ld seconds to sort %d elements.\n", (int)sortTime.tv_sec, sortTime.tv_nsec, MAX);

   return 0;

}
