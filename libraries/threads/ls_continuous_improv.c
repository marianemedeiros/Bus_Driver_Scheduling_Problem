#include "ls_continuous_improv.h"

void* local_search25_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	local_search_body(&pcr_continuous_improvement_foward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, 0);
    return NULL;
}

void* local_search26_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	local_search_body(&pcr_continuous_improvement_backward, solution_thread->thread_id, PCR_CN_B, solution_thread->log_file, 0);
    return NULL;
}

/***CONTINUOUS IMPROVEMENT FUNCTIONS OF K-SWAP (K = 1 ... 5) FOWARD AND BACKWARD. SO WE HAVE 10 FUNCTIONS.*******/
void* local_search27_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("1", KSWAP_CN_F);
	int k = 1;
	local_search_body(&kswap_continuous_improvement_foward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search28_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("1", KSWAP_CN_B);
	int k = 1;
	local_search_body(&kswap_continuous_improvement_backward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search29_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("2", KSWAP_CN_F);
	int k = 2;
	local_search_body(&kswap_continuous_improvement_foward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search30_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("2", KSWAP_CN_B);
	int k = 2;
	local_search_body(&kswap_continuous_improvement_backward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search31_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("3", KSWAP_CN_F);
	int k = 3;
	local_search_body(&kswap_continuous_improvement_foward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search32_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("3", KSWAP_CN_B);
	int k = 3;
	local_search_body(&kswap_continuous_improvement_backward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search33_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("4", KSWAP_CN_F);
	int k = 4;
	local_search_body(&kswap_continuous_improvement_foward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search34_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("4", KSWAP_CN_B);
	int k = 4;
	local_search_body(&kswap_continuous_improvement_backward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search35_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("5", KSWAP_CN_F);
	int k = 5;
	local_search_body(&kswap_continuous_improvement_foward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}

void* local_search36_P(void* solution){
	Solution_Thread* solution_thread = (Solution_Thread*) solution;
	char* n = concatKtoSwap("5", KSWAP_CN_B);
	int k = 5;
	local_search_body(&kswap_continuous_improvement_backward, solution_thread->thread_id, PCR_CN_F, solution_thread->log_file, k);
	free(n);
    return NULL;
}