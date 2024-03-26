#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <semaphore.h>
#include<time.h>
#include <sys/time.h>

#include "../operators/pcr.h"
#include "../operators/kswap.h"
#include "../shake.h"
#include "files.h"

#define NTHREADS OPERATORS
#define N_FUNC NTHREADS
#define K_MAX 4

#define printObjVNS(k, s_line) (fprintf(debug, "%d VNS: Melhorei::: shared_memory->f_obj: %f; \n", k, s_line))

int obj_value_constant;
int second_cond;
int double_way;
double time_constant;
double time_vnsp_2;

//#define COND1(flag) (flag)
//#define COND2(value) (value <= condition_criteria ? -1 : 1)
//#define CONDITION(value, flag) (condition_criteria != -1 ? (COND2(value)) : (COND1(flag)))

#define IMRPOV_COND(improv) (improv)
#define OBJ_COND(obj_value) (obj_value <= obj_value_constant ? -1 : 1)
#define OTHER_COND(obj_value, improv) (obj_value_constant != -1 ? (OBJ_COND(obj_value)) : (IMRPOV_COND(improv)))
#define TIME_COND(time_cond) (time_cond < time_constant ? 1 : -1)
#define CONDITION(obj_value, time_cond, improv) (time_constant != -1 ? (TIME_COND(time_cond)) : (OTHER_COND(obj_value, improv)))

int used_vns_p;
int used_local_search;

//variable that control vns iteration, but is global because is update at one of threads.
int vns_not_end;
int k; // VNS K, it's here because this variable is shared by all threads, but it's incremented only in VNS_P.
double obj_sm; // variable used in vns

//variable that control time of functions, to be saved at log files
struct timeval t1_copy, t2_copy, t1_shake, t2_shake, t1_thr_ex, t2_thr_ex;
double copy_executed;
double shake_executed;
double thread_executed;

//variable that are updated by all threads.
Solution* shared_memory;
Solution* best_solution;

Solution* sm_vet[NTHREADS];
Solution* s_shake;
int finished_functions;
//semaphores to control the update of variables that are shared by all threads.
sem_t semaphore_shared_memory;
sem_t semaphore_finished_functions;
sem_t semaphore_thread_executed;

//barrier
pthread_barrier_t barrier;

//conditional variables.
pthread_cond_t cond_start;
pthread_cond_t cond_vns;

//mutex that are used by conditional variables.
pthread_mutex_t mutex_start;
pthread_mutex_t mutex_vns;

//array of pointer functions.
void* (*p[N_FUNC]) (void* solution_thread);

//array of threads.
pthread_t threads[NTHREADS];

//scruct
typedef struct Solution_thread{
	int thread_id;
	FILE* log_file;
}Solution_Thread;

Solution_Thread** s_t;

// Functions
Solution_Thread** init_threads();
void join_threads(Solution_Thread** solutions_t);

Solution_Thread* inicialize_Solution_thread(int p_id);
void free_Solution_thread(Solution_Thread* s);

void local_search_body(Solution* (*fun_ptr)(Solution*,int, int), int thread_id, char* op_name, FILE* log_file, int k_swap);
void local_search_body_2(Solution* (*fun_ptr)(Solution*,int, int), int thread_id, char* op_name, FILE* log_file, int k_swap);

#endif