#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "definitions.h"

int main(int argc, char *argv[]){

    FILE *fp;
    int i;
    int elements=0;
    if(argc <=1) {
        fprintf(stdout, "Using max defined in definitions.h as number of elements to %d generate.\n", MAX);
        fprintf(stdout, "\nAlternate usage:\n./numGen [elemnts]\ne.g. ./numGen 1000\n");
        elements= MAX;
    }

    else
        elements = atoi(argv[1]);
    
    if((fp=fopen("rand.txt", "w")) == NULL){
        fprintf(stdout, "Cannot open rand.txt.\n");
        exit(-1);
    }

    //seed rand
    srand(time(NULL));
    int random;
    for(i=0;i<elements;i++){
        //rand number between 0 and 9,999,999 seperated by spaces
        random = rand() % 1000000; 
        fprintf(fp, "%d ", random);
    }
}
