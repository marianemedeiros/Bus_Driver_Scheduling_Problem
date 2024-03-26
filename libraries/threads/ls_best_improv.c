#include "ls_best_improv.h"

void* local_search3_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	local_search_body(&pcr_best_improvement_foward, solution_thread->thread_id, PCR_BS_F, solution_thread->log_file, 0);	
	return NULL;
}

void* local_search4_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	local_search_body(&pcr_best_improvement_backward, solution_thread->thread_id, PCR_BS_F, solution_thread->log_file, 0);	
    return NULL;
}

/***BEST IMPROVEMENT FUNCTIONS OF K-SWAP (K = 1 ... 5) FOWARD AND BACKWARD. SO WE HAVE 10 FUNCTIONS.*******/
void* local_search15_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("1", KSWAP_BS_F);
	int k = 1;
	local_search_body(&kswap_best_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search16_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("1", KSWAP_BS_B);
	int k = 1;
	local_search_body(&kswap_best_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search17_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("2", KSWAP_BS_F);
	int k = 2;
	local_search_body(&kswap_best_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search18_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("2", KSWAP_BS_B);
	int k = 2;
	local_search_body(&kswap_best_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search19_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("3", KSWAP_BS_F);
	int k = 3;
	local_search_body(&kswap_best_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search20_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("3", KSWAP_BS_B);
	int k = 3;
	local_search_body(&kswap_best_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search21_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("4", KSWAP_BS_F);
	int k = 4;
	local_search_body(&kswap_best_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search22_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("4", KSWAP_BS_B);
	int k = 4;
	local_search_body(&kswap_best_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search23_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("5", KSWAP_BS_F);
	int k = 5;
	local_search_body(&kswap_best_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search24_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("5", KSWAP_BS_B);
	int k = 5;
	local_search_body(&kswap_best_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
    return NULL;
}