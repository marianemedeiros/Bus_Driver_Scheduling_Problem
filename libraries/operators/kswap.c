#include "kswap.h"

char* concatKtoSwap(char* k, char* name){
	char* temp = (char*) calloc(256, sizeof(char));
	temp = strcat(temp, k);
	temp = strcat(temp, name);
	return temp;
}

int** build_cost_matrix_kswap(Journey** j1, Journey** j2, Journey** j3, int j1_s, int j2_s, int j3_s, int dm_m){
	#ifdef DEBUG_CG_SOLUTION
		printf("<<<build_cost_matrix_kswap2>>>\n");
	#endif
	int** cost_matrix = (int**) calloc(dm_m, sizeof(int*));

	for (int i = 0; i < dm_m; i++){
		cost_matrix[i] = (int*) calloc(dm_m, sizeof(int));
		for (int j = 0; j < dm_m; j++){
			//printf("%d - %d - %d\n", i, j, i);
			if((j1[i] != NULL && j2[j] != NULL && j3[i] != NULL)){// s1 + s2 + s3

				if(verifyViability(j1[i]->tasks, j2[j]->tasks->first->data) && verifyViability(j2[j]->tasks, j3[i]->tasks->first->data)){
					//printf("J1[%d] + J2[%d] + J3[%d]\n", i, j, i);
					j1[i]->tasks->last->next = j2[j]->tasks->first;
					j2[j]->tasks->last->next = j3[i]->tasks->first;
					j1[i]->tasks->size += j3[i]->tasks->size + j2[j]->tasks->size;
					
					//if(feasible(j1[i]))
					cost_matrix[i][j] = j1[i]->obj_function(j1[i]);
					//else
					//cost_matrix[i][j] = MAX_INF;

					#ifdef DEBUG_CG_SOLUTION
						printf("j1[%d] + j2[%d] + j3[%d]= %f , m: %d\n", i, j, i, aux, cost_matrix[i][j]); 
					#endif

					//printJourney(&j1[i], NULL);
					//printf("----------------------------------------------------------------\n");

					j1[i]->tasks->size -= (j2[j]->tasks->size + j3[i]->tasks->size);
					//tira o last->next do s2->j[j]
					j1[i]->tasks->last->next = NULL;
					j2[j]->tasks->last->next = NULL;

				}else{
					if(verifyViability(j1[i]->tasks, j2[j]->tasks->first->data)){
						joinTwoJourneysAndObj(j1[i], j2[j], &cost_matrix[i][j]);
						#ifdef DEBUG_CG_SOLUTION
							printf("IF1 J1[%d] + J2[%d] = %d; J3[%d] = %f; c: %f", i, j, cost_matrix[i][j], i, j3[i]->_obj, (cost_matrix[i][j]+j3[i]->_obj));
						#endif
						cost_matrix[i][j]+= j3[i]->_obj;

					}else if(verifyViability(j1[i]->tasks, j3[i]->tasks->first->data)){
						joinTwoJourneysAndObj(j1[i], j3[i], &cost_matrix[i][j]);
						#ifdef DEBUG_CG_SOLUTION
							printf("IF1 J1[%d] + J3[%d] = %d; J2[%d] = %f; c: %f ", i, i, cost_matrix[i][j], j, j2[j]->_obj, (cost_matrix[i][j]+j2[j]->_obj));
						#endif
						cost_matrix[i][j]+= j2[j]->_obj;

					}else if(verifyViability(j2[j]->tasks, j3[i]->tasks->first->data)){
						joinTwoJourneysAndObj(j2[j], j3[i], &cost_matrix[i][j]);
						#ifdef DEBUG_CG_SOLUTION
							printf("IF1 J2[%d] + J3[%d] = %d; J1[%d] = %f; c: %f\n", j, i, cost_matrix[i][j], j, j2[j]->_obj, (cost_matrix[i][j]+j2[j]->_obj));
						#endif
						cost_matrix[i][j]+= j1[i]->_obj;

					}else{
						#ifdef DEBUG_CG_SOLUTION
							printf("SOZINHOS\n");
						#endif
						cost_matrix[i][j] += j1[i]->_obj;;	
						cost_matrix[i][j]+= j2[j]->_obj;
						cost_matrix[i][j]+= j3[i]->_obj;
					}
				}
			}
			else if((j1[i] != NULL && j2[j] != NULL)){ //s1 + s2
				joinTwoJourneysAndObj(j1[i], j2[j], &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J1[%d] + J2[%d] = %d\n", i, j, cost_matrix[i][j]);
				#endif
				//printf("<<<%d>>>\n", cost_matrix[i][j]);
				//printf("----------------------------------------------------------------\n");
			}
			else if((j1[i] != NULL && j3[i] != NULL)){ // s1 + s3
				joinTwoJourneysAndObj(j1[i], j3[i], &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J1[%d] + J3[%d] = %d\n", i, i, cost_matrix[i][j]);
				#endif
			}
			else if((j1[i] != NULL)){ // s1
				joinTwoJourneysAndObj(j1[i], NULL, &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J1[%d] = %d\n", i , cost_matrix[i][j]);
				#endif
			}
			else if((j2[j] != NULL && j3[i] != NULL)){ // s2 + s3
				joinTwoJourneysAndObj(j2[j], j3[i], &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J2[%d] + J3[%d] = %d\n", j, i, cost_matrix[i][j]);
				#endif
			}
			else if((j2[j] != NULL)){ // s2
				joinTwoJourneysAndObj(j2[j], NULL, &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J2[%d] = %d\n", j, cost_matrix[i][j]);
				#endif
			}	
			else if((j3[i] != NULL)){ // s3
				joinTwoJourneysAndObj(j3[i], NULL, &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J3[%d] = %d\n", i, cost_matrix[i][j]);
				#endif
			}
			else{
				//printf("INVIÀVEL2\n");
				cost_matrix[i][j] = MAX_INF;	
			}
		}
	}
	//printMatrix(cost_matrix, dm_m);
	return cost_matrix;
}

Solution* generate_new_solution_kswap(int* f, int size_f, Journey** j1, Journey** j2, Journey** j3, int s_j1, int s_j2, int s_j3, int** m, int size_j){
	#ifdef DEBUG_CG_SOLUTION
		printf("generate_new_solution_kswap\n");
	#endif
	Solution* s = inicializeSolution(-1);
	for (int i = 0; i < size_f; i++){
		if((j1[i] != NULL && j2[f[i]] != NULL && j3[i] != NULL)){// s1 + s2 + s3
			if(j1[i]->tasks == NULL)
				printf("j1[%d]->tasks 'e NULLL\n", i);
			if(j2[f[i]]->tasks == NULL)
				printf("j2[%d]->tasks 'e NULLL\n", f[i]);
			if(j2[f[i]]->tasks == NULL)
				printf("j3[%d]->tasks 'e NULLL\n", i);

			if(verifyViability(j1[i]->tasks, j2[f[i]]->tasks->first->data) && verifyViability(j2[f[i]]->tasks, j3[i]->tasks->first->data)){
				justJoinJourneys(j2[f[i]], j3[i]);
				j2[f[i]]->tasks->size += j3[i]->tasks->size;
				free(j3[i]->tasks);
				free(j3[i]);

				justJoinJourneys(j1[i], j2[f[i]]);
				j1[i]->tasks->size += j2[f[i]]->tasks->size;
				j1[i]->key = i;	
				//j1[i]->_obj = j1[i]->obj_function(j1[i]);
				j1[i]->_obj = m[i][f[i]];
				s->f_obj += j1[i]->_obj;

				free(j2[f[i]]->tasks);
				free(j2[f[i]]);
				#ifdef DEBUG_CG_SOLUTION
					printf("IF1 j1[%d] + j2[%d] + j3[%d] = %f , m: %d\n", i, f[i], i, j1[i]->_obj, m[i][f[i]]);
				#endif
			}
			else if(joinJourneys(j1[i], j2[f[i]])){
				j1[i]->tasks->size += j2[f[i]]->tasks->size;
				j1[i]->key = i;	
				//j1[i]->_obj = j1[i]->obj_function(j1[i]);
				j1[i]->_obj = m[i][f[i]];
				s->f_obj += j1[i]->_obj;

				j1 = add_journey(&size_j, j3[i], j1);
				s_j1++;
				j1[size_j-1]->_obj = j3[i]->_obj;
				s->f_obj += j1[size_j-1]->_obj;	

				#ifdef DEBUG_CG_SOLUTION
					printf("IF1.2 j1[%d] + j2[%d] = %f , m: %d <<j3: %f>>\n", i, f[i], (j1[i]->_obj-j3[i]->_obj), m[i][f[i]], j3[i]->_obj);
				#endif

				free(j2[f[i]]->tasks);
				free(j2[f[i]]);
			}
			else if(joinJourneys(j1[i], j3[i])){
				j1[i]->tasks->size += j3[i]->tasks->size;
				j1[i]->key = i;	
				//j1[i]->_obj = j1[i]->obj_function(j1[i]);
				j1[i]->_obj = m[i][f[i]];
				s->f_obj += j1[i]->_obj;

				j1 = add_journey(&size_j, j2[f[i]], j1);
				s_j1++;
				j1[size_j-1]->_obj = j2[f[i]]->_obj;
				s->f_obj += j1[size_j-1]->_obj;	

				#ifdef DEBUG_CG_SOLUTION
					printf("IF1.3 j1[%d] + j3[%d] = %f , m: %d <<j2: %f>>\n", i, f[i], j1[i]->_obj, m[i][f[i]], j2[f[i]]->_obj);
				#endif

				free(j3[i]->tasks);
				free(j3[i]);
			}
			else if(joinJourneys(j2[f[i]], j3[i])){
				j2[f[i]]->tasks->size += j3[i]->tasks->size;
				j2[f[i]]->key = i;	
				
				j1 = add_journey(&size_j, j2[f[i]], j1);
				s_j1++;
				//j1[size_j-1]->_obj = j2[f[i]]->obj_function(j1[i]);
				j1[size_j-1]->_obj = m[i][f[i]];
				s->f_obj += j1[size_j-1]->_obj;

				#ifdef DEBUG_CG_SOLUTION
					printf("IF1.4 j2[%d] + j3[%d] = %f , m: %d <<j1: %f>>\n", i, f[i], j1[size_j-1]->_obj, m[i][f[i]], j1[i]->_obj);
				#endif

				s->f_obj += j1[i]->_obj;	
				free(j3[i]->tasks);
				free(j3[i]);
			}
			else{
				j1 = add_journey(&size_j, j2[f[i]], j1);
				s_j1++;
				j1[size_j-1]->_obj = j2[f[i]]->_obj;
				s->f_obj += j1[size_j-1]->_obj;				

				j1 = add_journey(&size_j, j3[i], j1);
				s_j1++;
				j1[size_j-1]->_obj = j3[i]->_obj;
				s->f_obj += j1[size_j-1]->_obj;	

				s->f_obj += j1[i]->_obj;
				#ifdef DEBUG_CG_SOLUTION
					printf("IF1.5 j1[%d] = %f, j2[%d] = %f, j3[%d] = %f,\n", i, j1[i]->_obj, f[i], j2[f[i]]->_obj, i, j3[i]->_obj);
				#endif
			}
		}
		else if((j1[i] != NULL && j2[f[i]] != NULL)){ //s1 + s2
			if(joinJourneys(j1[i], j2[f[i]])){
				j1[i]->tasks->size += j2[f[i]]->tasks->size;
				j1[i]->key = i;
				//j1[i]->_obj = j1[i]->obj_function(j1[i]);
				j1[i]->_obj = m[i][f[i]];
				s->f_obj += j1[i]->_obj;
				free(j2[f[i]]->tasks);
				free(j2[f[i]]);
				#ifdef DEBUG_CG_SOLUTION
					printf("j1[%d] + j2[%d] = %f , m: %d\n", i, f[i], j1[i]->_obj, m[i][f[i]]);
				#endif
			}else{
				j1 = add_journey(&size_j, j2[f[i]], j1);
				s_j1++;
				j1[size_j-1]->_obj = j2[f[i]]->_obj;
				s->f_obj += j1[size_j-1]->_obj;
				s->f_obj += j1[i]->_obj;		
				#ifdef DEBUG_CG_SOLUTION
					printf("j1[%d] = %f j2[%d] = %f , m: %d\n", i, j1[i]->_obj ,f[i], j1[size_j-1]->_obj, m[i][f[i]]);
				#endif
			}
		}
		else if((j1[i] != NULL && j3[i] != NULL)){ // s1 + s3
			if(joinJourneys(j1[i], j3[i])){
				j1[i]->tasks->size += j3[i]->tasks->size;
				j1[i]->key = i;
				//j1[i]->_obj = j1[i]->obj_function(j1[i]);
				j1[i]->_obj = m[i][f[i]];
				s->f_obj += j1[i]->_obj;
				free(j3[i]->tasks);
				free(j3[i]);
				
				#ifdef DEBUG_CG_SOLUTION
					printf("j1[%d] + j3[%d] = %f , m: %d\n", i, i, j1[i]->_obj, m[i][f[i]]);
				#endif

			}else{
				j1 = add_journey(&size_j, j3[i], j1);
				s_j1++;	
				j1[size_j-1]->_obj = j3[i]->_obj;
				s->f_obj += j1[size_j-1]->_obj;
				s->f_obj += j1[i]->_obj;		
				
				#ifdef DEBUG_CG_SOLUTION
					printf("j1[%d] = %f j3[%d] = %f , m: %d\n", i, j1[i]->_obj ,i, j3[i]->_obj, m[i][f[i]]);
				#endif
			}
		}
		else if((j2[f[i]] != NULL && j3[i] != NULL)){ // s2 + s3
			if(joinJourneys(j2[f[i]], j3[i])){
				j2[f[i]]->tasks->size += j3[i]->tasks->size;
				j2[f[i]]->key = f[i];
				//j2[f[i]]->_obj = j2[f[i]]->obj_function(j2[f[i]]);
				j2[f[i]]->_obj = m[i][f[i]];
				s->f_obj += j2[f[i]]->_obj;
				
				j1 = add_journey(&size_j, j2[f[i]], j1);
				s_j1++;	
				free(j3[i]->tasks);
				free(j3[i]);

				#ifdef DEBUG_CG_SOLUTION
					printf("j2[%d] + j3[%d] = %f , m: %d\n", f[i], i, j1[size_j-1]->_obj, m[i][f[i]]);
				#endif
			}else{
				j1 = add_journey(&size_j, j2[f[i]], j1);
				s_j1++;
				j1[size_j-1]->_obj = j2[f[i]]->_obj;
				s->f_obj += j1[size_j-1]->_obj;				

				j1 = add_journey(&size_j, j3[i], j1);
				s_j1++;
				j1[size_j-1]->_obj = j3[i]->_obj;
				s->f_obj += j1[size_j-1]->_obj;	

				#ifdef DEBUG_CG_SOLUTION
					printf("j2[%d] = %f j3[%d] = %f , m: %d\n", f[i], j2[f[i]]->_obj ,i, j1[size_j-1]->_obj, m[i][f[i]]);
				#endif
			}
		}
		else if((j1[i] != NULL)){ // s1
			s->f_obj += j1[i]->_obj;				
			#ifdef DEBUG_CG_SOLUTION
				printf("j1[%d] = %f m: %d\n", i, j1[i]->_obj, m[i][f[i]]);
			#endif
		}
		else if((j2[f[i]] != NULL)){ // s2
			j1 = add_journey(&size_j, j2[f[i]], j1);
			s_j1++;
			j1[size_j-1]->_obj = j2[f[i]]->_obj;
			#ifdef DEBUG_CG_SOLUTION
				printf("j2[%d] = %f m: %d\n", f[i], j1[size_j-1]->_obj, m[i][f[i]]);
			#endif
			s->f_obj += j1[size_j-1]->_obj;				
		}	
		else if((j3[i] != NULL)){ // s3
			j1 = add_journey(&size_j, j3[i], j1);
			s_j1++;
			j1[size_j-1]->_obj = j3[i]->_obj;
			#ifdef DEBUG_CG_SOLUTION
				printf("j3[%d] = %f m: %d\n", i, j1[size_j-1]->_obj, m[i][f[i]]);
			#endif
			s->f_obj += j1[size_j-1]->_obj;				
		}
	}
	s->j = reorganizeJourneys(s->j, j1, size_j, s_j1);
	s->size_j = s_j1;

	#ifdef DEBUG_CG_SOLUTION
		printf("SOLUTION OBJ: %f\n", s->f_obj);
	#endif
		
	return s;
}

/*************************************************************KSWAP FIRST IMPROVEMENT*******************************************************************************************************
*****************************************************************************************************************************************************************************************/
Solution* kswap_first_improvement_foward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	VectorTuple* vt = breakVector(K, k, LAYERS_SIZE, 0);
	int s1 = 0, s2 = 0, s3 = 0;
	for (int i = 0; i < vt->size; i++){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j3 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0, s3 = 0;
		cut2places(s->j, s->size_j, vt->v1[i], vt->v2[i], j1, j2, j3, &s1, &s2, &s3);
		int dm_m = max(s1, s2, s3, s->size_j);

		int** m = build_cost_matrix_kswap(j1, j2, j3, s1, s2, s3, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		if(OBJ(s->f_obj, sum)){
			Solution* s_line = generate_new_solution_kswap(f, dm_m, j1, j2, j3, s1, s2, s3, m, s->size_j);
			//printf("sum: %d (s: %f)\n\n", sum, s->f_obj);
			#ifdef DEBUG_OP
				printKswap(thread_id, k, KSWAP_FI_F,  vt->v1[i], vt->v2[i], s_line->f_obj, s->f_obj, sum);
			#endif

			#ifdef CALCULE_COST
				calculeCostFunction(s_line);
			#endif

			freeCostMatrix(m, dm_m);
			free(j2);
			free(j3);
			free(f);
			freeSolution(s);
			free(s);

			freeVectorTuple(vt);
			free(K);
			return s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
			freeJourneys(j3, s->size_j);
		}
		
		freeCostMatrix(m, dm_m);
		free(j2);
		free(j3);
		free(f);
	}

	freeVectorTuple(vt);
	free(K);
	return s;
}

Solution* kswap_first_improvement_backward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	VectorTuple* vt = breakVector(K, k, LAYERS_SIZE, 0);
	int s1 = 0, s2 = 0, s3 = 0;
	for (int i = vt->size-1; i >= 0; i--){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j3 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0, s3 = 0;
		cut2places(s->j, s->size_j, vt->v1[i], vt->v2[i], j1, j2, j3, &s1, &s2, &s3);
		int dm_m = max(s1, s2, s3, s->size_j);

		int** m = build_cost_matrix_kswap(j1, j2, j3, s1, s2, s3, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		if(OBJ(s->f_obj, sum)){
			Solution* s_line = generate_new_solution_kswap(f, dm_m, j1, j2, j3, s1, s2, s3, m, s->size_j);
			//printf("sum: %d (s: %f)\n\n", sum, s->f_obj);
			#ifdef DEBUG_OP
				printKswap(thread_id, k, KSWAP_FI_B,  vt->v1[i], vt->v2[i], s_line->f_obj, s->f_obj, sum);
			#endif

			#ifdef CALCULE_COST
				calculeCostFunction(s_line);
			#endif

			freeCostMatrix(m, dm_m);
			free(j2);
			free(j3);
			free(f);
			freeSolution(s);
			free(s);

			freeVectorTuple(vt);
			free(K);
			return s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
			freeJourneys(j3, s->size_j);
		}

		freeCostMatrix(m, dm_m);
		free(j2);
		free(j3);
		free(f);
	}
	freeVectorTuple(vt);
	free(K);
	return s;
}

/*************************************************************KSWAP BEST IMPROVEMENT*******************************************************************************************************
*****************************************************************************************************************************************************************************************/
Solution* kswap_best_improvement_foward(Solution* s, int k, int thread_id){
	Solution* best = copySolution(s);
	int* K = generate_cut_places(best->j);
	VectorTuple* vt = breakVector(K, k, LAYERS_SIZE, 0);
	Solution* s_line;
	int s1 = 0, s2 = 0, s3 = 0;

	for (int i = 0; i < vt->size; i++){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j3 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0, s3 = 0;
		cut2places(s->j, s->size_j, vt->v1[i], vt->v2[i], j1, j2, j3, &s1, &s2, &s3);
		int dm_m = max(s1, s2, s3, s->size_j);

		int** m = build_cost_matrix_kswap(j1, j2, j3, s1, s2, s3, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		//printf("---------sum: %d (%f)\n\n", sum, best->f_obj);
		if(OBJ(best->f_obj, sum)){
			s_line = generate_new_solution_kswap(f, dm_m, j1, j2, j3, s1, s2, s3, m, s->size_j);
			//printf("sum: %d (s: %f)\n\n", sum, best->f_obj);
			#ifdef DEBUG_OP
				printKswap(thread_id, k, KSWAP_BS_F,  vt->v1[i], vt->v2[i], s_line->f_obj, best->f_obj, sum);
			#endif

			#ifdef CALCULE_COST
				calculeCostFunction(s_line);
			#endif
			//free s
			freeSolution(best);
			free(best);
			best = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
			freeJourneys(j3, s->size_j);
		}

		freeCostMatrix(m, dm_m);
		free(j2);
		free(j3);
		free(f);
	}
	freeVectorTuple(vt);
	free(K);
	freeSolution(s);
	free(s);
	return best;
}

Solution* kswap_best_improvement_backward(Solution* s, int k, int thread_id){
	Solution* best = copySolution(s);

	int* K = generate_cut_places(best->j);
	VectorTuple* vt = breakVector(K, k, LAYERS_SIZE, 0);
	Solution* s_line;
	int s1 = 0, s2 = 0, s3 = 0;

	for (int i = vt->size-1; i >= 0; i--){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j3 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0, s3 = 0;
		cut2places(s->j, s->size_j, vt->v1[i], vt->v2[i], j1, j2, j3, &s1, &s2, &s3);
		int dm_m = max(s1, s2, s3, s->size_j);

		int** m = build_cost_matrix_kswap(j1, j2, j3, s1, s2, s3, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		//printf("---------sum: %d (%f)\n\n", sum, best->f_obj);
		if(OBJ(best->f_obj, sum)){
			s_line = generate_new_solution_kswap(f, dm_m, j1, j2, j3, s1, s2, s3, m, s->size_j);
			//printf("sum: %d (s: %f)\n\n", sum, best->f_obj);
			#ifdef DEBUG_OP
				printKswap(thread_id ,k ,KSWAP_BS_B,  vt->v1[i], vt->v2[i], s_line->f_obj, best->f_obj, sum);
			#endif

			#ifdef CALCULE_COST
				calculeCostFunction(s_line);
			#endif
			//free s
			freeSolution(best);
			free(best);
			best = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
			freeJourneys(j3, s->size_j);
		}
		freeCostMatrix(m, dm_m);
		free(j2);
		free(j3);
		free(f);
	}
	freeVectorTuple(vt);
	free(K);

	freeSolution(s);
	free(s);

	return best;
}

/*************************************************************KSWAP CONTINUOUS IMPROVEMENT*******************************************************************************************************
*****************************************************************************************************************************************************************************************/
Solution* kswap_continuous_improvement_foward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	VectorTuple* vt = breakVector(K, k, LAYERS_SIZE, 0);
	Solution* s_line;
	int s1 = 0, s2 = 0, s3 = 0;

	for (int i = 0; i < vt->size; i++){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j3 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0, s3 = 0;
		cut2places(s->j, s->size_j, vt->v1[i], vt->v2[i], j1, j2, j3, &s1, &s2, &s3);
		int dm_m = max(s1, s2, s3, s->size_j);

		int** m = build_cost_matrix_kswap(j1, j2, j3, s1, s2, s3, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		if(OBJ(s->f_obj, sum)){
			s_line = generate_new_solution_kswap(f, dm_m, j1, j2, j3, s1, s2, s3, m, s->size_j);
			//printf("%d - sum: %f (s: %f)\n", k, sum, s->f_obj);

			#ifdef DEBUG_OP
				printKswap(thread_id, k, KSWAP_CN_F, vt->v1[i], vt->v2[i], s_line->f_obj, s->f_obj, sum);
			#endif
			//free s
			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
			freeJourneys(j3, s->size_j);
		}

		freeCostMatrix(m, dm_m);
		free(j2);
		free(j3);
		free(f);
	}
	freeVectorTuple(vt);
	free(K);

	#ifdef CALCULE_COST
		calculeCostFunction(s);
	#endif

	return s;
}

Solution* kswap_continuous_improvement_backward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	VectorTuple* vt = breakVector(K, k, LAYERS_SIZE, 0);
	Solution* s_line;
	int s1 = 0, s2 = 0, s3 = 0;

	for (int i = vt->size-1; i >= 0; i--){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j3 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0, s3 = 0;
		cut2places(s->j, s->size_j, vt->v1[i], vt->v2[i], j1, j2, j3, &s1, &s2, &s3);
		int dm_m = max(s1, s2, s3, s->size_j);

		int** m = build_cost_matrix_kswap(j1, j2, j3, s1, s2, s3, dm_m);
		//printMatrix(m, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		//printf("sum: %d (s: %f)\n", sum, s->f_obj);
		if(OBJ(s->f_obj, sum)){
			s_line = generate_new_solution_kswap(f, dm_m, j1, j2, j3, s1, s2, s3, m, s->size_j);
			//printf("-- sum: %d (s_line: %f)\n", sum, s_line->f_obj);
			//if(sum != (int) s_line->f_obj)
			//	printf("EEERROOOO\n");
			#ifdef DEBUG_OP
				printKswap(thread_id, k, KSWAP_CN_B, vt->v1[i], vt->v2[i], s_line->f_obj, s->f_obj, sum);
			#endif
			//free s
			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
			freeJourneys(j3, s->size_j);
		}

		freeCostMatrix(m, dm_m);
		free(j2);
		free(j3);
		free(f);

		//break;
	}
	freeVectorTuple(vt);
	free(K);

	#ifdef CALCULE_COST
		calculeCostFunction(s);
	#endif

	return s;
}