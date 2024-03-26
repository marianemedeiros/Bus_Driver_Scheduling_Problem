#ifndef LS_BEST_IMPROV_H
#define LS_BEST_IMPROV_H

#include "threads.h"

/*PCR BEST IMPROVEMENT FUNCTIONS*/
void* local_search3_P(void* solution_thread);
void* local_search4_P(void* solution_thread);

/*KSWAP BEST IMPROVEMENT FUNCTIONS*/
void* local_search15_P(void* solution_thread);
void* local_search16_P(void* solution_thread);
void* local_search17_P(void* solution_thread);
void* local_search18_P(void* solution_thread);
void* local_search19_P(void* solution_thread);
void* local_search20_P(void* solution_thread);
void* local_search21_P(void* solution_thread);
void* local_search22_P(void* solution_thread);
void* local_search23_P(void* solution_thread);
void* local_search24_P(void* solution_thread);

#endif