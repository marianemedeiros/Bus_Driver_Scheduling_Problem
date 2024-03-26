#ifndef CUT_H
#define CUT_H

#include "solution.h"

void printCutJounerys(Journey** j1, Journey** j2, Journey** j3, int size);
int* generate_cut_places();
int generate_cut_places_shake(Solution* s, int shake2);
void verifyCutPlace(Solution* s, int k, int* s1_i, int* s2_i);
void cut(Journey** j, int size_j, int k, Journey** j1, Journey** j2, int* s1_i, int* s2_i);
void cut2(Journey** j, int size_j, int k, Journey** j1, Journey** j2, int* s1_i, int* s2_i);
void cut2places(Journey** j, int size_j, int k1, int k2,Journey** j1, Journey** j2, Journey** j3, int* s1_i, int* s2_i, int* s3_i);
#endif