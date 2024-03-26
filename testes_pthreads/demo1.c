#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 5

typedef struct test{
  int i;
  double j;
}Test;


Test* copy(Test** from){
  Test* rt = (Test*) calloc(1, sizeof(Test));
  rt->i = (*from)->i;
  rt->j = (*from)->j;
  return rt;
}

void *ls(void* ls_id){
  sleep(1);
  Test* id = (Test*) ls_id;
 
  
  if(id->i == 0){
    printf("Local Search 0 - %d ,  %f\n", id->i, id->j);
    for(int i=0; i<(id->j*10);i++);
    printf("Finish Ls0\n");
  }
  if(id->i == 1){
    printf("Local Search 1 - %d ,  %f\n", id->i, id->j);
    for(int i=0; i<(id->j*10);i++);
    printf("Finish Ls1\n");
  }
  /*if(id == 2)
    printf("Local Search 2\n");
  */

  return NULL;
}

int main(){
  int err;
  Test* t = (Test*) calloc(1, sizeof(Test));
  t->i = -1;
  t->j = 1.5;


  pthread_t tid; //thread id, used to identify the thread in the system.

  printf("Before Thread\n");
  
  /* create a thread. 
    first arg: is a pointer to thread id.
    second arg:
    third arg: is the function that will be executed by the thread.
    fourth arg: is used to pass arguments to thread. */
  for (int i = 0; i < 2; i++){
    Test* arg = copy(&t);
    arg->i = i;
    arg->j = 1.5 * (i*200000);

    printf("%d  \n", i);
    err = pthread_create(&tid, NULL, ls, (void*)arg);  
    if(err != 0)
      printf("\nCan't create thread: [%s]", strerror(err));
    else
      printf("Thread created. \n");
    
  }
  
  free(t);
  // will wait all threads terminate.
  pthread_join(tid, NULL);
  printf("After Thread\n");
}