#include "shake.h"

Journey** recombineJourneys(int* size_j, Journey** j1, Journey** j2, double* recombinations, int sj1, int sj2, double* obj){
	int* aux2 = (int*) calloc(sj2, sizeof(int));
	int modified = 0;
	for (int i = 0; i < sj1; i++){
			for (int j = 0; j < sj2; j++){
				if(aux2[j] == 0 && joinJourneys(j1[i], j2[j])){
					j1[i]->tasks->size += j2[j]->tasks->size;
					j1[i]->key = i;	

					j1[i]->_obj = j1[i]->obj_function(j1[i]);
					(*obj)+= j1[i]->_obj;
			
					free(j2[j]->tasks);
					free(j2[j]);
					modified = 1;
					aux2[j] = 1;
					j = sj2;
				}
			}
	}
	for (int i = 0; i < sj2; i++){
		if(aux2[i] == 0){
			j1 = (Journey**) realloc(j1, (sj1+1)* sizeof(Journey*));
			j1[sj1] = j2[i];
			j1[sj1]->key = i;
			j1[sj1]->_obj = j1[sj1]->obj_function(j1[sj1]);	
			(*obj)+= j1[sj1]->_obj;
			sj1++;		
		}
	}
	
	if(modified == 1)
		(*recombinations)++;

	free(aux2);
	*size_j = sj1;
	return j1;
}

Journey** recombineJourneys1(int* size_j, Journey** j1, Journey** j2, double* recombinations, int sj1, int sj2, double* obj){
	//printf("recombineJourneys\n");
	int* aux2 = (int*) calloc(sj2, sizeof(int));
	int modified = 0;
	for (int i = 0; i < sj1; i++){
			for (int j = 0; j < sj2; j++){
				if(aux2[j] == 0 && verifyViability(j1[i]->tasks, j2[j]->tasks->first->data)){
					Node* aux_j1 = j1[i]->tasks->last;
					Node* aux_j2 = j2[j]->tasks->first;

					joinJourneys(j1[i], j2[j]);
					j1[i]->tasks->size += j2[j]->tasks->size;

					double aux_obj = j1[i]->obj_function(j1[i]);

					if(feasible(j1[i])){
						//printf("It's feasible, j1_size: %d, \n", j1[i]->tasks->size);
						j1[i]->key = i;	

						j1[i]->_obj = aux_obj;
						(*obj)+= j1[i]->_obj;
			
						free(j2[j]->tasks);
						free(j2[j]);
						modified = 1;
						aux2[j] = 1;
						j = sj2;
					}else{
						//printf("disJoinJourneys\n");
						disJoinJourneys(j1[i], j2[j], aux_j1, aux_j2);
						j1[i]->tasks->size -= j2[j]->tasks->size;
						aux_obj = 0;
					}
				}
			}
	}

	for (int i = 0; i < sj2; i++){
		if(aux2[i] == 0){
			j1 = (Journey**) realloc(j1, (sj1+1)* sizeof(Journey*));
			j1[sj1] = j2[i];
			j1[sj1]->key = i;
			j1[sj1]->_obj = j1[sj1]->obj_function(j1[sj1]);	
			(*obj)+= j1[sj1]->_obj;
			sj1++;	
		}
	}
	
	if(modified == 1)
		(*recombinations)++;

	free(aux2);
	*size_j = sj1;
	return j1;
}

Journey** shake1slice(Solution* s, double p){
	double recombinations = 0.0;
	while(recombinations < p){
		int sliceN = generate_cut_places_shake(s, 0);
		//sliceN = 239;
		//printf("shake1slice sliceN: %d\n", sliceN);
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		int sj1 = 0, sj2 = 0;
		cut2(s->j, s->size_j,sliceN, j1, j2, &sj1, &sj2);

		//free s->j
		freeJourneys(s->j, s->size_j);
		free(s->j);
		s->j = recombineJourneys(&s->size_j, j1,j2, &recombinations, sj1, sj2, &s->f_obj);			
		//printf("shake1slice SOLUTION OBJ:: %f ; REC: %f\n", s->f_obj, recombinations);
		free(j2);
		//break;
	}
	return s->j;
}


Journey** shake2slice(Solution* s, double p){
	double recombinations = 0.0;

	while(recombinations < p){
		int sliceN = generate_cut_places_shake(s, 1);
		int sliceN2 = sliceN + 60;
		//printf("c1: %d, c2: %d\n", sliceN, sliceN2);
		//printf("shake2slice sliceN: %d, sliceN2: %d\n", sliceN, sliceN2);
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j_aux = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j3 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		int s1 = 0, s_aux = 0, s2 = 0, s3 = 0;

		cut2(s->j, s->size_j, sliceN, j1, j_aux, &s1, &s_aux);
		//free s->j
		freeSolution(s);
		s->j = recombineJourneys(&s->size_j, j1, j_aux, &recombinations, s1, s_aux, &s->f_obj);
		free(j_aux);

		cut2(s->j, s->size_j, sliceN2, j2, j3, &s2, &s3);
		//free s->j
		freeSolution(s);
		s->j = recombineJourneys(&s->size_j, j2, j3, &recombinations, s2, s3, &s->f_obj);					
		free(j3);
		//printf("shake2slice SOLUTION OBJ:: %f ; REC: %f\n", s->f_obj, recombinations);
	}
	return s->j;
}


Solution* shake(Solution* s, int k){
	s->f_cost = 0;
	s->f_obj = 0;
	double fat1 = 0.15;
	double fat2 = 0.30;

	if(k == 1){
		s->j = shake2slice(s, (s->size_j*fat1));
	}
	if(k == 2){
		s->j = shake1slice(s, (s->size_j*fat1));
	}
	if(k == 3){
		s->j = shake1slice(s, (s->size_j*fat2));
	}
	if(k == 4){
		s->j = shake2slice(s, (s->size_j*fat2));
	}
	s->f_cost = 0.0;
	s->duration = 0.0;
	return s;
}