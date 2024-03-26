#include "functions.h"

int randNum(int size){
	if(size == 0)
		size++;
	return rand() % size;
}

Solution* inicializeSolution(){
	Solution* s = (Solution*) calloc(1,sizeof(Solution));
	s->index_pwd = 0;
	s->a = 0;
	return s;
}

void inicializeSemaphores(){
	for (int i = 0; i < NTHREADS; i++){
		sem_init(&semaphores[i], 0, 1);
	}
}

void runSharedMemory(int i){
	for (int j = 0; j < NTHREADS; j++){
		if(j != i && buffer[j] != NULL){
			sem_wait(&semaphores[j]);
			if(buffer[j]->a > buffer[i]->a){
				printf("THREAD %d - Vou atualizar (de %d para %d) (i %d - j %d)\n", i, buffer[i]->a, buffer[j]->a, i, j);
				buffer[i]->a = buffer[j]->a;
				buffer[i]->pwd[buffer[i]->index_pwd] = j;
				buffer[i]->index_pwd++;		
			}	
			sem_post(&semaphores[j]);				
		}
	}
}

void write_sharedMemory(int i){
	//printf("Oi eu sou a THREAD %d e estou alterando a memória principal.\n", i);

	if(buffer[i] == NULL){
		buffer[i] = inicializeSolution();
		buffer[i]->a = randNum(i*10);
		buffer[i]->pwd[buffer[i]->index_pwd] = i;
		buffer[i]->index_pwd++;
		printf("THREAD %d - a: %d; pwd: %d; index: %d\n\n", i, buffer[i]->a, buffer[i]->pwd[buffer[i]->index_pwd-1], buffer[i]->index_pwd);
	}else{
		printf("Ja tem algo, futuramente iremos comparar\n");
	}
}

void* f_op1(void* P_id){
	int* i = (int*) P_id;
	sem_wait(&semaphores[*i]);
	write_sharedMemory(*i);
	sem_post(&semaphores[*i]);

	runSharedMemory(*i);
	return NULL;
}

void* f_op2(void* P_id){
	int* i = (int*) P_id;
	sem_wait(&semaphores[*i]);
	write_sharedMemory(*i);
	sem_post(&semaphores[*i]);
	runSharedMemory(*i);
	return NULL;
}

void* f_op3(void* P_id){
	int* i = (int*) P_id;
	sem_wait(&semaphores[*i]);
	write_sharedMemory(*i);
	sem_post(&semaphores[*i]);
	runSharedMemory(*i);
	return NULL;
}

void* f_op4(void* P_id){
	int* i = (int*) P_id;
	sem_wait(&semaphores[*i]);
	write_sharedMemory(*i);
	sem_post(&semaphores[*i]);
	runSharedMemory(*i);
	return NULL;
}

void* f_op5(void* P_id){
	int* i = (int*) P_id;
	sem_wait(&semaphores[*i]);
	write_sharedMemory(*i);
	sem_post(&semaphores[*i]);
	runSharedMemory(*i);
	return NULL;
}