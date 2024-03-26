#include "functions.h"

int main(){
	pthread_t threads[NTHREADS];
	buffer = (Solution**) calloc(NTHREADS,sizeof(Solution*));
	inicializeSemaphores();

	/*
	for (int i = 0; i < NTHREADS; i++){
		if(buffer[i] == NULL){
			buffer[i] = inicializeSolution();
			buffer[i]->a = randNum(i*10);
			buffer[i]->pwd[buffer[i]->index_pwd] = i;
			buffer[i]->index_pwd++;
			printf("a: %d;\nbuffer[]: %d;\nindex: %d\n\n", buffer[i]->a, buffer[i]->pwd[buffer[i]->index_pwd-1], buffer[i]->index_pwd);
		}
	}
	*/

	p[0] = f_op1;
	p[1] = f_op2;
	p[2] = f_op3;
	p[3] = f_op4;
	p[4] = f_op5;
	
	for(int i = 0; i < NTHREADS; i++){
		int* x = (int*) calloc(1, sizeof(int));
		*x = i;
		pthread_create(&(threads[i]), NULL, p[i], x);
		//free(x);  
	}

	for (int i = 0; i < NTHREADS; i++){
		pthread_join(threads[i], NULL);  
	}
	
	for (int i = 0; i < NTHREADS; i++){
		printf("%d - A: %d; pwd: ", i, buffer[i]->a);
		for (int j = 0; j < buffer[i]->index_pwd; j++){
			printf(" %d ", buffer[i]->pwd[j]);
		}
		printf("\n");
	}
	
}
