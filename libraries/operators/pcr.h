#ifndef PCR_H
#define PCR_H


#include "operators.h"

Solution* pcr_first_improvement_foward(Solution* s, int k, int thread_id);
Solution* pcr_first_improvement_backward(Solution* s, int k, int thread_id);

Solution* pcr_best_improvement_foward(Solution* s, int k, int thread_id);
Solution* pcr_best_improvement_backward(Solution* s, int k, int thread_id);

Solution* pcr_continuous_improvement_foward(Solution* s, int k, int thread_id);
Solution* pcr_continuous_improvement_backward(Solution* s, int k, int thread_id);


#endif