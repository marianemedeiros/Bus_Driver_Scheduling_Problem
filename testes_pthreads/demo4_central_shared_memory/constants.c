#include "files.h"
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 2
#define N_FUNC NTHREADS

typedef struct Solution{
   int a;   
   int pwd[NTHREADS];
   int index_pwd;
}Solution;

Solution* buffer;

void* (*p[N_FUNC]) (void* x);
sem_t semaphore;





