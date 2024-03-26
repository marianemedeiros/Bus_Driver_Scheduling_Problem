#include "functions.h"

#define BUFFER_LOG_INFOS "BUFFER_LOG_INFOS.txt"
#define BUFFER_LOG_DETAILS "BUFFER_LOG_DETAILS.txt"

int main(){
	time_t tm;
	srand((unsigned) time(&tm));

	char* n1 = nameFile(PWD, BUFFER_LOG_INFOS);
	char* n2 = nameFile(PWD, BUFFER_LOG_DETAILS);

	buffer_infos = openFile(n1, "w");
	fprintf(buffer_infos, "execution_time; local_search_id; cost_function; objective_function\n");
	buffer_details = openFile(n2, "w");

	pthread_t threads[NTHREADS];
	buffer = NULL;
	sem_init(&semaphore, 0, 1);


	p[0] = f_op1;
	p[1] = f_op2;
	//p[2] = f_op3;
	//p[3] = f_op4;
	//p[4] = f_op5;
	
	for(int i = 0; i < NTHREADS; i++){
		int* x = (int*) calloc(1, sizeof(int));
		*x = i;
		pthread_create(&(threads[i]), NULL, p[i], x);
		//free(x);  
	}

	#define START_THREAD

	for (int i = 0; i < NTHREADS; i++){
		pthread_join(threads[i], NULL);  
	}
	printf("aa\n");
	printf("sharedMemory: %d\n", buffer->a);

	closeFile(buffer_infos);
	closeFile(buffer_details);
}
