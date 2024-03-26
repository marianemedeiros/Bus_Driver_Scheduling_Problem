#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>


typedef struct vectorTuple{
	int* v1;
	int* v2;
	int size;
}VectorTuple;

void printVectorTuple(VectorTuple* v);
void printVector(int* v, int size);
void printMatrix(int** m, int dm_m);
void freeVectorTuple(VectorTuple* v);
int* copyVector(int* V, int* v_to, int from, int to);
int** combinationsOfVector(int* vector, int k, int size, int reverse);
VectorTuple* breakVector(int* vector, int k, int size, int reverse);

#endif