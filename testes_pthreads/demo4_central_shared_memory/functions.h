#include "constants.c"

#define LS1_INFOS "local_search1_infos.txt"
#define LS1_DETAILS "local_search1_details.txt"

#define LS2_INFOS "local_search2_infos.txt"
#define LS2_DETAILS "local_search2_details.txt"

#define LS3_INFOS "local_search3_infos.txt"
#define LS3_DETAILS "local_search3_details.txt"

#define LS4_INFOS "local_search4_infos.txt"
#define LS4_DETAILS "local_search4_details.txt"

#define LS5_INFOS "local_search5_infos.txt"
#define LS5_DETAILS "local_search5_details.txt"

Solution* inicializeSolution();
int acess_sharedMemory(Solution* x, int i);

void* f_op1(void* P_id);
void* f_op2(void* P_id);
void* f_op3(void* P_id);
void* f_op4(void* P_id);
void* f_op5(void* P_id);
