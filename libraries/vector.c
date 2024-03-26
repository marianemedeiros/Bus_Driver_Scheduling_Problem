#include "vector.h"

void printVectorTuple(VectorTuple* v){
	printf("\nV1:\n");
	for (int i = 0; i < v->size; i++){
		printf("%d ", v->v1[i]);
	}
	printf("\nV2:\n");
	for (int i = 0; i < v->size; i++){
		printf("%d ", v->v2[i]);
	}
}

void printVector(int* v, int size){
	for (int i = 0; i < size; i++)
		printf(" %d ", v[i]);
	printf("\n");
}

void printMatrix(int** m, int dm_m){
	for (int i = 0; i < dm_m; i++){
		printf("%d - ", i);
		for (int j = 0; j < dm_m; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

VectorTuple* inicializeVectorTuple(int size){
	VectorTuple* vectorTuple = (VectorTuple*) calloc(1, sizeof(VectorTuple));
	vectorTuple->v1 = (int*) calloc(size, sizeof(int));
	vectorTuple->v2 = (int*) calloc(size, sizeof(int));
	vectorTuple->size = size;
	return vectorTuple;
}

void freeVectorTuple(VectorTuple* v){
	free(v->v1);
	free(v->v2);
	free(v);
}

int* copyVector(int* V, int* v_to, int from, int to){
	int j = 0;
	for (int i = from; i < to; i++){
		v_to[j] = V[i];
		j++;
	}
	return v_to;
}

int** declareMatrix(int l, int c){
	int** m = (int**) calloc(l, sizeof(int*));
	for (int i = 0; i < l; i++){
		m[i] = (int*) calloc(c, sizeof(int));
	}
	return m;
}

int verifyLines(int k, int size){
	int i = 0, tam = 0;
	while((i+k) < size){
		i = i + k;
		tam++;
	}
	if(i < size)
		tam++;
	return tam;
}

VectorTuple* breakVector(int* vector, int k, int size, int reverse){
	VectorTuple* rt = inicializeVectorTuple(size-k);

	if(reverse){
		rt->v2 = copyVector(vector, rt->v2, 0, size-k);
		rt->v1 = copyVector(vector, rt->v1, k, size);
	}else{
		rt->v1 = copyVector(vector, rt->v1, 0, size-k);
		rt->v2 = copyVector(vector, rt->v2, k, size);
	}

	rt->size = size-k;
	return rt;
}

int** combinationsOfVector(int* v, int k, int size, int reverse){
	int** m = (int**) calloc(verifyLines(k,size), sizeof(int*));
	
	if(reverse == 0){
		int i = 0, z = 0;
		while((i+k) < size){
			m[z] = copyVector(v, m[z], i, i+k);
			i = i + k;
			z++;
		}

		if(i < size){
			int diff = k - (size - i);
			m[z] = copyVector(v, m[z], i-diff,size);
		}	
	}else{
		int i = size, z = 0;
		while((i-k) >= 0){
			m[z] = copyVector(v, m[z], i-k, i);
			i = i - k;
			z++;
		}
		if(i-k < 0){
			int a = (-1) * (i-k);
			m[z] = copyVector(v, m[z] , 0, (i+a));
		}
	}
	return m;
}

