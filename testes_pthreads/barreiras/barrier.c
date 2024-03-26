#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define THREAD_COUNT 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void* threadFn(void *id_ptr) {
    pthread_mutex_lock(&mutex); //mutex lock
    pthread_cond_wait(&condition, &mutex); //wait for the condition
    int thread_id = *(int*)id_ptr;
    printf("<<<<<<<<<<<<<<<<<T%d condição foi satisfeita então eu irei trabalhar.\n", thread_id);
    pthread_mutex_unlock(&mutex);

 return NULL;
}


int main() {
  int i;
  pthread_t threads[THREAD_COUNT];

  for (i=0; i < THREAD_COUNT; i++) {
    pthread_create(&threads[i], NULL, threadFn, &i);
  }

  pthread_cond_broadcast(&condition);
  //sleep(10);
  
  /*printf("Join ...\n");
  for (i=0; i < THREAD_COUNT; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("acabou join\n");
  */
  return 0;
}