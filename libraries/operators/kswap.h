#ifndef KSWAP_H
#define KSWAP_H

#include "operators.h"

char* concatKtoSwap(char* k, char* name);

Solution* kswap_first_improvement_foward(Solution* s, int k, int thread_id);
Solution* kswap_first_improvement_backward(Solution* s, int k, int thread_id);

Solution* kswap_best_improvement_foward(Solution* s, int k, int thread_id);
Solution* kswap_best_improvement_backward(Solution* s, int k, int thread_id);

Solution* kswap_continuous_improvement_foward(Solution* s, int k, int thread_id);
Solution* kswap_continuous_improvement_backward(Solution* s, int k, int thread_id);

#endif