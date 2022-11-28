/*
 * File used to determind time used by each merge sort.
 * Note do not use clock()
 *
 */

#include <time.h>
#include <unistd.h>

enum {NS_PER_SECOND = 1000000000};

void getTimeDelta(struct timespec t1, struct timespec t2, struct timespec *td){
    //subtract nano seconds, then seconds from end - start
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec = t2.tv_sec - t1.tv_sec;
    
    if(td->tv_sec > 0 && td->tv_nsec < 0){
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0){
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

