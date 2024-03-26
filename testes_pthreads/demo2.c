#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
#define N_FUNC 10
#define BUFFER 1000

int buffer[BUFFER];
int buffer_id = 0;

pthread_mutex_t buffer_mutex;
sem_t buffer_full, buffer_empty;

void write_sharedMemory(int i){
	//sem_wait(&buffer_full);
	pthread_mutex_lock(&buffer_mutex);
	printf("Oi eu sou a THREAD %d e estou alterando a memória principal para %d \n", i, i);

	if(buffer[i-1] != -1){
		buffer[i] = buffer[i-1] + i;
		printf("buffer[i] = %d; buffer[i-1] + i = %d;\n", buffer[i] , (buffer[i-1] + i));
		buffer_id++;
	}else{
		buffer[i] = i;
		printf("buffer[i] = %d;\n", buffer[i]);
		buffer_id++;
	}

	pthread_mutex_unlock(&buffer_mutex);
	//sem_post(&buffer_empty);
}

void* f_op1(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op2(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op3(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op4(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op5(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op6(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op7(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op8(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op9(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* f_op10(void* P_id){
	int* i = (int*) P_id;
	write_sharedMemory(*i);
}

void* (*p[N_FUNC]) (void* x);

int main(){
	pthread_t threads[NTHREADS];

	pthread_mutex_init(&buffer_mutex, NULL);
	sem_init(&buffer_full, 0 , BUFFER);
	sem_init(&buffer_empty, 0 , 0);

	p[0] = f_op1;
	p[1] = f_op2;
	p[2] = f_op3;
	p[3] = f_op4;
	p[4] = f_op5;
	p[5] = f_op6;
	p[6] = f_op7;
	p[7] = f_op8;
	p[8] = f_op9;
	p[9] = f_op10;

	for (int i = 0; i < BUFFER; i++){
		buffer[i] = -1;
	}

	for(int i = 0; i < NTHREADS; i++){
		int* x = (int*) calloc(1, sizeof(int));
		*x = i;
		pthread_create(&(threads[i]), NULL, p[i], x);  
	}

	for (int i = 0; i < NTHREADS; i++){
		pthread_join(threads[i], NULL);  
	}

	for (int i = 0; i < buffer_id; i++){
		printf("%d \n", buffer[i]);
	}
}
