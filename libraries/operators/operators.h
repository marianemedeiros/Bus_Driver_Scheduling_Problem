#ifndef OPERATORS_H
#define OPERATORS_H

#include "../cut.h"

#define CALCULE_COST 
//#define DEBUG_OP 

#define COST_OBJ(s1_obj, s1_cost, s2_obj, s2_cost) (((s2_obj < s1_obj) || (s2_cost < s1_cost)) ? 1 : 0)
#define OBJ(s1_obj, s2_obj) ((s2_obj < s1_obj) ? 1 : 0)

#define printPcr(thr_id, op, cut, s_line, s, sum) (fprintf(debug, "(BL%d)  %s - cut: %d; s_line obj: %f; s atual obj: %f; (sum: %f)\n", thr_id, op, cut, s_line, s, sum))
#define printKswap(thr_id, k, type, cut1, cut2, s_line, s, z_p) (fprintf(debug, "(BL%d)  %d%s  - cut:%d-%d; s_line obj: %f; s atual obj: %f; (sum: %f)\n", thr_id, k, type, cut1, cut2, s_line, s, sum))

void printResultVectorAPC(int* f, int** m, int dm);
int verify_viabilityT(Solution* s, char* c);
void freeCostMatrix(int** m, int dm);
int max(int a, int b, int c, int d);

#endif