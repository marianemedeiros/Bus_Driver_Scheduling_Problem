#include "ls_first_improv.h"

void* local_search1_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	local_search_body(&pcr_first_improvement_foward, solution_thread->thread_id, PCR_FI_F, solution_thread->log_file, 0);
	return NULL;
}

void* local_search2_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	local_search_body(&pcr_first_improvement_backward, solution_thread->thread_id, PCR_FI_B, solution_thread->log_file, 0);
	return NULL;
}

/***FIRST IMPROVEMENT FUNCTIONS OF K-SWAP (K = 1 ... 5) FOWARD AND BACKWARD. SO WE HAVE 10 FUNCTIONS.*******/
void* local_search5_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int k = 1;
	char* n = concatKtoSwap("1", KSWAP_FI_F);
	local_search_body(&kswap_first_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search6_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int k = 1;
	char* n = concatKtoSwap("1", KSWAP_FI_B);
	local_search_body(&kswap_first_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search7_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int k = 2;
	char* n = concatKtoSwap("2", KSWAP_FI_F);
	local_search_body(&kswap_first_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search8_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	int k = 2;
	char* n = concatKtoSwap("2", KSWAP_FI_B);
	local_search_body(&kswap_first_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search9_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("3", KSWAP_FI_F);
	int k = 3;
	local_search_body(&kswap_first_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search10_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("3", KSWAP_FI_B);
	int k = 3;
	local_search_body(&kswap_first_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search11_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("4", KSWAP_FI_F);
	int k = 4;
	local_search_body(&kswap_first_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search12_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("4", KSWAP_FI_B);
	int k = 4;
	local_search_body(&kswap_first_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search13_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("5", KSWAP_FI_F);
	int k = 5;
	local_search_body(&kswap_first_improvement_foward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}

void* local_search14_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("5", KSWAP_FI_B);
	int k = 5;
	local_search_body(&kswap_first_improvement_backward, solution_thread->thread_id, n, solution_thread->log_file, k);
	free(n);
	return NULL;
}