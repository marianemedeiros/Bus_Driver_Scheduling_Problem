// gcc -fopenmp -o go go.c
// ./go

#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv){

int i, thread_id, nloops;

#pragma omp parallel private(thread_id, nloops)
{
    nloops = 0;

#pragma omp for
    for (i=0; i<1000; ++i)
      ++nloops;
    
    //omp_get_thread_num: Returns the thread number of the thread, within the team, making this call. 
    //This number will be between 0 and OMP_GET_NUM_THREADS-1. The master thread of the team is thread 0
    thread_id = omp_get_thread_num();

    printf("Thread %d performed %d iterations of the loop.\n", thread_id, nloops );
}// fim do pragma

  return 0;
}