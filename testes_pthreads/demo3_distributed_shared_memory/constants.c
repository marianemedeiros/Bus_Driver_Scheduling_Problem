#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 5
#define N_FUNC 5

typedef struct Solution{
   int a;   
   int pwd[NTHREADS];
   int index_pwd;
}Solution;

Solution** buffer;

void* (*p[N_FUNC]) (void* x);
sem_t semaphores[NTHREADS];



