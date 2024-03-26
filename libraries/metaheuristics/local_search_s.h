#ifndef LOCAL_SEARCH_S_H
#define LOCAL_SEARCH_S_H

#include "vns.h"


Solution* vnd(Solution* s, int k_line_max);
Solution* local_search_1(Solution* s);
Solution* local_search_2(Solution* s);
Solution* adap_search_3(Solution* s);

#endif