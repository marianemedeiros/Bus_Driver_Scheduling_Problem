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

Solution* generateSolution(int i){
	Solution* newSolution= inicializeSolution();
	newSolution->a = randNum(i*10);
	printf("THREAD %d - a: %d;\n\n", i, newSolution->a);
	return newSolution;
}


int acess_sharedMemory(Solution* x, int i){
	if(buffer == NULL){
		buffer = x;
		return 1;
	}else if(x->a > buffer->a){//atualiza a memória principal
		buffer->a = x->a;
		return 1;
	}else if(x->a < buffer->a){//atuliza a solução da thread
		x->a = buffer->a;
		return 0;
	}
	//COLOCAR ESCRITA DE ARQUIVO DA MEMORIA PRINCIPAL AQUI
	return -1;
}

void writeFileInfos(FILE* file, double executed_m , int id, Solution* buffer){
	fprintf(file, "%f; %d; %d; %d\n", executed_m, id, buffer->a, buffer->a);
}

void writeFileDetails(FILE* file, int id, Solution* buffer){
	fprintf(file, "%d; \n %d \n\n", id, buffer->a);
}

void* f_op1(void* P_id){
	int* i = (int*) P_id;

	#ifndef START_THREAD
		printf("thread %d já criada, porém START_THREAD ainda não definida, vamos esperar ...\n", *i);
	#endif

	#ifdef START_THREAD
		printf("START_THREAD definida, vamos começar\n");
		char* n1 = nameFile(PWD, LS1_INFOS);
		FILE* ls_infos = openFile(n1, "w");

		char* n2 = nameFile(PWD, LS1_DETAILS);
		FILE* ls_details = openFile(n2, "w");
		
		//inicio busca
		int it = 0;
		while(it <= *i){
			clock_t time_s = clock();
			Solution* x = generateSolution(*i);

			sem_wait(&semaphore);
			int rt = acess_sharedMemory(x,*i);
			sem_post(&semaphore);
			printf("s%d: %d\n", *i, x->a);
			clock_t time_f = clock();
			double executed_m = (double)(time_s - time_f) / CLOCKS_PER_SEC;

			//atualizando arquivos de log da thread
			writeFileInfos(ls_infos, executed_m , *i, buffer);
			writeFileDetails(ls_details, *i, buffer);

			//atualizando arquivos de log da memória principal
			if(rt == 1){
				writeFileInfos(buffer_infos, executed_m , *i, buffer);
				writeFileDetails(buffer_details, *i, buffer);
			}
			it++;
		//fim da busca		
		}

		closeFile(ls_infos);
		closeFile(ls_details);
		return NULL;
	#endif
}

void* f_op2(void* P_id){
	int* i = (int*) P_id;
	#ifndef START_THREAD
		printf("thread %d já criada, porém START_THREAD ainda não definida, vamos esperar ...\n", *i);
	#endif

	#ifdef START_THREAD
		printf("START_THREAD definida, vamos começar\n");

		char* n1 = nameFile(PWD, LS2_INFOS);
		FILE* ls_infos = openFile(n1, "w");

		char* n2 = nameFile(PWD, LS2_DETAILS);
		FILE* ls_details = openFile(n2, "w");
		
		//inicio busca
		int it = 0;
		while(it <= *i){
			clock_t time_s = clock();
			Solution* x = generateSolution(*i);

			sem_wait(&semaphore);
			int rt = acess_sharedMemory(x,*i);
			sem_post(&semaphore);
			printf("s%d: %d\n", *i, x->a);
			clock_t time_f = clock();
			double executed_m = (double)(time_s - time_f) / CLOCKS_PER_SEC;

			//atualizando arquivos de log da thread
			writeFileInfos(ls_infos, executed_m , *i, buffer);
			writeFileDetails(ls_details, *i, buffer);

			//atualizando arquivos de log da memória principal
			if(rt == 1){
				writeFileInfos(buffer_infos, executed_m , *i, buffer);
				writeFileDetails(buffer_details, *i, buffer);
			}
			it++;
		//fim da busca	
		}
		closeFile(ls_infos);
		closeFile(ls_details);
		return NULL;
	#endif
}


void* f_op3(void* P_id){
	int* i = (int*) P_id;

	char* n1 = nameFile(PWD, LS3_INFOS);
	FILE* ls_infos = openFile(n1, "w");

	char* n2 = nameFile(PWD, LS3_DETAILS);
	FILE* ls_details = openFile(n2, "w");
	
	//inicio busca
	int it = 0;
	while(it <= *i){
		clock_t time_s = clock();
		Solution* x = generateSolution(*i);

		sem_wait(&semaphore);
		int rt = acess_sharedMemory(x,*i);
		sem_post(&semaphore);
		printf("s%d: %d\n", *i, x->a);
		clock_t time_f = clock();
		double executed_m = (double)(time_s - time_f) / CLOCKS_PER_SEC;

		//atualizando arquivos de log da thread
		writeFileInfos(ls_infos, executed_m , *i, buffer);
		writeFileDetails(ls_details, *i, buffer);

		//atualizando arquivos de log da memória principal
		if(rt == 1){
			writeFileInfos(buffer_infos, executed_m , *i, buffer);
			writeFileDetails(buffer_details, *i, buffer);
		}
		it++;
	//fim da busca		
	}

	closeFile(ls_infos);
	closeFile(ls_details);
	return NULL;
}


void* f_op4(void* P_id){
	int* i = (int*) P_id;

	char* n1 = nameFile(PWD, LS4_INFOS);
	FILE* ls_infos = openFile(n1, "w");

	char* n2 = nameFile(PWD, LS4_DETAILS);
	FILE* ls_details = openFile(n2, "w");
	
	//inicio busca
	int it = 0;
	while(it <= *i){
		clock_t time_s = clock();
		Solution* x = generateSolution(*i);

		sem_wait(&semaphore);
		int rt = acess_sharedMemory(x,*i);
		sem_post(&semaphore);
		printf("s%d: %d\n", *i, x->a);
		clock_t time_f = clock();
		double executed_m = (double)(time_s - time_f) / CLOCKS_PER_SEC;

		//atualizando arquivos de log da thread
		writeFileInfos(ls_infos, executed_m , *i, buffer);
		writeFileDetails(ls_details, *i, buffer);

		//atualizando arquivos de log da memória principal
		if(rt == 1){
			writeFileInfos(buffer_infos, executed_m , *i, buffer);
			writeFileDetails(buffer_details, *i, buffer);
		}
		it++;
	//fim da busca		
	}


	closeFile(ls_infos);
	closeFile(ls_details);
	return NULL;
}


void* f_op5(void* P_id){
	int* i = (int*) P_id;

	char* n1 = nameFile(PWD, LS5_INFOS);
	FILE* ls_infos = openFile(n1, "w");

	char* n2 = nameFile(PWD, LS5_DETAILS);
	FILE* ls_details = openFile(n2, "w");
	
	//inicio busca
	int it = 0;
	while(it <= *i){
		clock_t time_s = clock();
		Solution* x = generateSolution(*i);

		sem_wait(&semaphore);
		int rt = acess_sharedMemory(x,*i);
		sem_post(&semaphore);
		printf("s%d: %d\n", *i, x->a);
		clock_t time_f = clock();
		double executed_m = (double)(time_s - time_f) / CLOCKS_PER_SEC;

		//atualizando arquivos de log da thread
		writeFileInfos(ls_infos, executed_m , *i, buffer);
		writeFileDetails(ls_details, *i, buffer);

		//atualizando arquivos de log da memória principal
		if(rt == 1){
			writeFileInfos(buffer_infos, executed_m , *i, buffer);
			writeFileDetails(buffer_details, *i, buffer);
		}
		it++;
	//fim da busca		
	}


	closeFile(ls_infos);
	closeFile(ls_details);
	return NULL;
}
