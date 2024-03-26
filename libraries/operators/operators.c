#include "operators.h"

void printResultVectorAPC(int* f, int** m, int dm){
	double soma = 0;
	for (int i = 0; i < dm; i++){
		printf("%d %d = %d\n", i, f[i], m[i][f[i]]);
		soma+= (double)m[i][f[i]];
	}
	//printf("SOMA: %f\n", soma);
}

int verify_viabilityT(Solution* s, char* c){

	int rt = 0;
	for (int i = 0; i < s->size_j; i++){
		Node* aux = s->j[i]->tasks->first;
		while(aux->next != NULL){
			Task* current = aux->data;
			Task* next = aux->next->data;
			
			if(current->destination != next->origin && !compareDateTime(current->end_time, next->start_time)){
				rt = 1;
				printf("<<%s>>%c - %c :: %d - %d \n", c,current->destination, next->origin, current->end_time->hours2minutes, next->start_time->hours2minutes);
				printTask(current, s->j[i]->key, s->j[i]->realDuration, NULL);
				printf("\n");
				printTask(next, s->j[i]->key, s->j[i]->realDuration, NULL);
				printf("\n\n");
			}
			aux = aux->next;
		}
	}
	return rt;
}

void freeCostMatrix(int** m, int dm){
	for (int i = 0; i < dm; i++) {
		free(m[i]);
	}
	free(m);
}

int max(int a, int b, int c, int d){
	int r = 0;
	if(a >= b && a >= c && a >= d)
		r = a;
	else if(b >= a && b >= c && b >= d)
		r = b;
	else if(c >= a && c >= b && c >= d)
		r = c;
	else if(d >= a && d >= b && d >= c)
		r = d;
	return r;
}
