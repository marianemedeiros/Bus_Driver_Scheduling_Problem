#include "ls_first_improv.h"

void* local_search1_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = pcr_first_improvement_foward(copySolution(s), 0);

		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;
		
		//compare local search s with shared memory s.
		sem_wait(&semaphore);

		s_line = acess_sharedMemory(s_line,thread_id, executed_t, PCR_FI_F, 1);

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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, PCR_FI_F, 1);
	}while(flag_r);
	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &pcr_first_improvement_foward, thread_id, PCR_FI_F, solution_thread->log_file, 0);
	
	freeSolution(s);
	free(s);

	return NULL;
}

void* local_search2_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = pcr_first_improvement_backward(copySolution(s), 0);
		clock_t time_f = clock();
		double executed_t = (double)(time_f - time_s) / CLOCKS_PER_SEC;
		//compare local search s with shared memory s.
		sem_wait(&semaphore);
		s_line = acess_sharedMemory(s_line,thread_id, executed_t, PCR_FI_B, 1);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_cost, s->size_j, PCR_FI_B, 1);
	}while(flag_r);
	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &pcr_first_improvement_backward, thread_id, PCR_FI_B, solution_thread->log_file, 0);

	freeSolution(s);
	free(s);

	return NULL;
}

/***FIRST IMPROVEMENT FUNCTIONS OF K-SWAP (K = 1 ... 5) FOWARD AND BACKWARD. SO WE HAVE 10 FUNCTIONS.*******/
void* local_search5_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("1", KSWAP_FI_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_foward(copySolution(s), 1);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
		
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_foward, thread_id, n, solution_thread->log_file, 1);


	free(n);
	freeSolution(s);
	free(s);
	return NULL;
}

void* local_search6_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("1", KSWAP_FI_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_backward(copySolution(s), 1);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_backward, thread_id, n, solution_thread->log_file, 1);

	free(n);
	freeSolution(s);
	free(s);
	
	return NULL;
}

void* local_search7_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("2", KSWAP_FI_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_foward(copySolution(s), 2);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_foward, thread_id, n, solution_thread->log_file, 2);

	free(n);
	freeSolution(s);
	free(s);

	return NULL;
}

void* local_search8_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("2", KSWAP_FI_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_backward(copySolution(s), 2);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_backward, thread_id, n, solution_thread->log_file, 2);


	free(n);
	freeSolution(s);
	free(s);

	return NULL;
}

void* local_search9_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("3", KSWAP_FI_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_foward(copySolution(s), 3);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_foward, thread_id, n, solution_thread->log_file, 3);

	free(n);
	freeSolution(s);
	free(s);
	
	return NULL;
}

void* local_search10_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("3", KSWAP_FI_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_backward(copySolution(s), 3);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);
	
	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_backward, thread_id, n, solution_thread->log_file, 3);

	free(n);
	freeSolution(s);
	free(s);
	
	return NULL;
}

void* local_search11_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("4", KSWAP_FI_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_foward(copySolution(s), 4);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);

	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_foward, thread_id, n, solution_thread->log_file, 4);


	free(n);
	freeSolution(s);
	free(s);

	return NULL;
}

void* local_search12_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("4", KSWAP_FI_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_backward(copySolution(s), 4);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_backward, thread_id, n, solution_thread->log_file, 4);


	free(n);
	freeSolution(s);
	free(s);


	return NULL;
}

void* local_search13_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("5", KSWAP_FI_F);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_foward(copySolution(s), 5);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_foward, thread_id, n, solution_thread->log_file, 5);

	free(n);
	freeSolution(s);
	free(s);

	return NULL;
}

void* local_search14_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int thread_id = solution_thread->thread_id;
	Solution* s = solution_thread->s;
	char* n = concatKtoSwap("5", KSWAP_FI_B);

	int flag_r = 0;
	do{
		flag_r = 0;
		clock_t time_s = clock();
		Solution* s_line = kswap_first_improvement_backward(copySolution(s), 5);
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
		writeFileInfos(solution_thread->log_file, executed_t , thread_id, s->f_cost, s->f_obj, s->size_j, n, 1);
	}while(flag_r);

	////////////////// SECOND WHILE 
	//s = second_local_search(s, solution_thread->k, &kswap_first_improvement_backward, thread_id, n, solution_thread->log_file, 5);

	free(n);
	freeSolution(s);
	free(s);

	return NULL;
}