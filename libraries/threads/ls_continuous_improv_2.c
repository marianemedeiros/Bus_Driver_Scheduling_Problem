#include "ls_continuous_improv.h"

void* local_search25_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;

	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = pcr_continuous_improvement_foward(copySolution(s), 0);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, PCR_CN_F, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);
			flag_r = 1;
			s = s_line;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, PCR_CN_F, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &pcr_continuous_improvement_foward, thread_id, PCR_CN_F, solution_thread->log_file, 0);

	freeSolution(s);
	free(s);

    return NULL;
}

void* local_search26_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = pcr_continuous_improvement_backward(copySolution(s), 0);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, PCR_CN_B, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, PCR_CN_B, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &pcr_continuous_improvement_backward, thread_id, PCR_CN_B, solution_thread->log_file, 0);

	freeSolution(s);
	free(s);
    return NULL;
}

/***CONTINUOUS IMPROVEMENT FUNCTIONS OF K-SWAP (K = 1 ... 5) FOWARD AND BACKWARD. SO WE HAVE 10 FUNCTIONS.*******/
void* local_search27_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("1", KSWAP_CN_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_foward(copySolution(s), 1);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;


		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);

	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_foward, thread_id, n, solution_thread->log_file, 1);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search28_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("1", KSWAP_CN_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_backward(copySolution(s), 1);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_backward, thread_id, n, solution_thread->log_file, 1);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search29_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("2", KSWAP_CN_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_foward(copySolution(s), 2);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_foward, thread_id, n, solution_thread->log_file, 2);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search30_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("2", KSWAP_CN_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_backward(copySolution(s), 2);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_backward, thread_id, n, solution_thread->log_file, 2);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search31_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	

	char* n = concatKtoSwap("3", KSWAP_CN_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_foward(copySolution(s), 3);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_foward, thread_id, n, solution_thread->log_file, 3);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search32_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("3", KSWAP_CN_B);


	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_backward(copySolution(s), 3);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_backward, thread_id, n, solution_thread->log_file, 3);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search33_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("4", KSWAP_CN_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_foward(copySolution(s), 4);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_foward, thread_id, n, solution_thread->log_file, 4);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search34_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("4", KSWAP_CN_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_backward(copySolution(s), 4);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_backward, thread_id, n, solution_thread->log_file, 4);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search35_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("5", KSWAP_CN_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_foward(copySolution(s), 5);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif

			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_foward, thread_id, n, solution_thread->log_file, 5);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}

void* local_search36_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	
	
	char* n = concatKtoSwap("5", KSWAP_CN_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_continuous_improvement_backward(copySolution(s), 5);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;

		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, n, 1);
		sem_post(&semaphore);

		//compare s_line with local search s.
		if(OBJ(s->f_obj, s_line->f_obj)){
			#ifdef DEBUG_LS
				printObjBL(thread_id, s_line->f_obj);
			#endif
				
			freeSolution(s);
			free(s);

			s = s_line;
			flag_r = 1;
		}else{
			freeSolution(s_line);
			free(s_line);
		}
		//update log file of thread.	
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE
	//s = second_local_search(s, solution_thread->k, &kswap_continuous_improvement_backward, thread_id, n, solution_thread->log_file, 5);

	free(n);
	freeSolution(s);
	free(s);
    return NULL;
}