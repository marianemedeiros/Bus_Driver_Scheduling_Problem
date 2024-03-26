#include "pcr.h"

int** build_cost_matrix(Journey** j1, Journey** j2, int j1_s, int j2_s, int dm_m){
	#ifdef DEBUG_CG_SOLUTION
		printf("build_cost_matrix\n");
	#endif

	int** cost_matrix = (int**) calloc(dm_m, sizeof(int*));
	for (int i = 0; i < dm_m; i++){
		cost_matrix[i] = (int*) calloc(dm_m, sizeof(int));
		for (int j = 0; j < dm_m; j++){
			if(j1[i] != NULL && j2[j] != NULL){// s1 + s2
				if(verifyViability(j1[i]->tasks, j2[j]->tasks->first->data)){
					//printf("----------------------------------------------------------------\n");
					joinTwoJourneysAndObj(j1[i], j2[j], &cost_matrix[i][j]);
					#ifdef DEBUG_CG_SOLUTION
						printf("j1[%d] + j2[%d] = %d\n", i, j, cost_matrix[i][j]); 
					#endif
					//printf("----------------------------------------------------------------\n");
				}else{
					#ifdef DEBUG_CG_SOLUTION
						printf("---> j1[%d] + j2[%d] \n", i, j);
					#endif
					//cost_matrix[i][j] = MAX_INF;
					cost_matrix[i][j] = j1[i]->obj_function(j1[i]);
					cost_matrix[i][j] += j2[j]->obj_function(j2[j]);	
				}
			}
			else if(j1[i] != NULL){ // s1
				//printf("----------------------------------------------------------------\n");
				joinTwoJourneysAndObj(j1[i], NULL, &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J1: j1[%d] = %f , m: %d <<<<<%f>>>>\n", i, j1[i]->_obj, cost_matrix[i][j], j1[i]->_obj); 
				#endif
				//printf("----------------------------------------------------------------\n");
			}
			else if(j2[j] != NULL){ // s2
				//printf("----------------------------------------------------------------\n");
				joinTwoJourneysAndObj(j2[j], NULL, &cost_matrix[i][j]);
				#ifdef DEBUG_CG_SOLUTION
					printf("J2: j2[%d] = %f , m: %d <<<<<%f>>>>\n", j, j2[j]->_obj, cost_matrix[i][j], j2[j]->_obj); 
				#endif
				//printf("----------------------------------------------------------------\n");
			}
			else{
				cost_matrix[i][j] = MAX_INF;	
			}
		}
	}
	//printMatrix(cost_matrix, dm_m);
	return cost_matrix;
}

//generating a new solution by pointers manipulation.
Solution* generate_new_solution(int* f, int size_f, Journey** j1, Journey** j2, int s_j1, int s_j2, int** m, int size_j){
	#ifdef DEBUG_CG_SOLUTION
		printf("generate_new_solution\n");
	#endif

	Solution* s = inicializeSolution(-1);
	for (int i = 0; i < size_f; i++){
		if(j2[f[i]] != NULL && j1[i] != NULL){//combine s1 + s2
			if(j1[i]->tasks == NULL)
				printf("j1[%d]->tasks 'e NULLL\n", i);
			if(j2[f[i]]->tasks == NULL)
				printf("j2[%d]->tasks 'e NULLL\n", f[i]);
			
			if(verifyViability(j1[i]->tasks, j2[f[i]]->tasks->first->data)){
				joinJourneys(j1[i], j2[f[i]]);
				j1[i]->tasks->size += j2[f[i]]->tasks->size;
				j1[i]->key = i;	

				j1[i]->_obj = m[i][f[i]];
				s->f_obj += j1[i]->_obj;
				#ifdef DEBUG_CG_SOLUTION
					printf("j1[%d] + j2[%d] = %f , m: %d\n", i, f[i], j1[i]->_obj, m[i][f[i]]); 
				#endif
				//printJourney(&j1[i], NULL);
				//printf("----------------------------------------------------------------\n");
				free(j2[f[i]]->tasks);
				free(j2[f[i]]);
			}else{
				j1 = add_journey(&size_j, j2[f[i]], j1);
				s_j1++;
				j1[size_j-1]->_obj = j2[f[i]]->_obj;
				s->f_obj += m[i][f[i]];
				//s->f_obj += j1[i]->_obj;
				#ifdef DEBUG_CG_SOLUTION
					printf("NC J2 j1[%d] = %f; j2[%d] = %f , m: %d\n", i, j1[i]->_obj, f[i], j1[size_j-1]->_obj, m[i][f[i]]);
				#endif
				//printJourney(&j1[s_j1-1], NULL);
				//printf("----------------------------------------------------------------\n");
			}
		}
		else if(j1[i] == NULL && j2[f[i]] != NULL){//combine s2
			j1 = add_journey(&size_j, j2[f[i]], j1);
			s_j1++;
			j1[size_j-1]->_obj = j2[f[i]]->_obj;
			//s->f_obj += j1[size_j-1]->_obj;
			s->f_obj += m[i][f[i]];
			#ifdef DEBUG_CG_SOLUTION
				printf("N1 NULL J2 j1[%d] + j2[%d] = %f , m: %d\n", i, f[i], j1[size_j-1]->_obj, m[i][f[i]]);
			#endif
			//printJourney(&j1[s_j1-1], NULL);
			//printf("----------------------------------------------------------------\n");

		}else if(j1[i] != NULL && j2[f[i]] == NULL){
			j1[i]->_obj = j1[i]->_obj;
			s->f_obj += m[i][f[i]];
			#ifdef DEBUG_CG_SOLUTION
				printf("N2 NULL J1 j1[%d] = %f , m: %d\n", i, j1[i]->_obj, m[i][f[i]]);
			#endif
		}
	}
	s->j = reorganizeJourneys(s->j, j1, size_j, s_j1);
	s->size_j = s_j1;
	#ifdef DEBUG_CG_SOLUTION
		printf("SOLUTION OBJ: %f\n", s->f_obj);
	#endif
	return s;
}

/*************************************************************PCR FIRST IMPROVEMENT*******************************************************************************************************
*****************************************************************************************************************************************************************************************/
Solution* pcr_first_improvement_foward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	int s1 = 0, s2 = 0;
	for (int i = 0; i < LAYERS_SIZE; i++){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0;
		cut(s->j, s->size_j, K[i], j1, j2, &s1, &s2);
		int dm_m = max(s1, s2, 0, s->size_j);
		
		int** m = build_cost_matrix(j1, j2, s1, s2, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		//printf("sum: %f (%f)\n", sum, s->f_obj);
		if(OBJ(s->f_obj, sum)){
			Solution* s_line = generate_new_solution(f,dm_m,j1, j2, s1, s2, m, s->size_j);
			//printf("----sum: %f (%f)\n\n", sum, s_line->f_obj);
			#ifdef DEBUG_OP
				printPcr(thread_id, PCR_FI_F, K[i], s_line->f_obj, s->f_obj, sum);
			#endif

			#ifdef CALCULE_COST
				calculeCostFunction(s_line);
			#endif

			freeCostMatrix(m, dm_m);
			free(j2);
			free(f);
			freeSolution(s);
			free(s);
			free(K);
			return s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
		}
		
		freeCostMatrix(m, dm_m);
		free(j2);
		free(f);
		break;
	}
	free(K);
	return s;
}

Solution* pcr_first_improvement_backward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	int s1 = 0, s2 = 0;
	for (int i = LAYERS_SIZE-1; i >= 0; i--){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0;
		cut(s->j, s->size_j, K[i], j1, j2, &s1, &s2);
		int dm_m = max(s1, s2, 0, s->size_j);
		
		int** m = build_cost_matrix(j1, j2, s1, s2, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		if(OBJ(s->f_obj, sum)){
			Solution* s_line = generate_new_solution(f,dm_m,j1, j2, s1, s2, m, s->size_j);
			//printf("sum: %d (%f)\n\n", sum, s->f_obj);
			#ifdef DEBUG_OP
				printPcr(thread_id, PCR_FI_B, K[i], s_line->f_obj, s->f_obj, sum);
			#endif

			#ifdef CALCULE_COST
				calculeCostFunction(s_line);
			#endif

			freeCostMatrix(m, dm_m);
			free(j2);
			free(f);
			freeSolution(s);
			free(s);
			free(K);
			return s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
		}

		freeCostMatrix(m, dm_m);
		free(j2);
		free(f);
	}

	free(K);
	return s;
}

/*************************************************************PCR BEST IMPROVEMENT*******************************************************************************************************
*****************************************************************************************************************************************************************************************/
Solution* pcr_best_improvement_foward(Solution* s, int k, int thread_id){
	Solution* best = copySolution(s);
	int* K = generate_cut_places(best->j);
	Solution* s_line;
	int s1 = 0, s2 = 0;

	for (int i = 0; i < LAYERS_SIZE; i++){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0;
		cut(s->j, s->size_j, K[i], j1, j2, &s1, &s2);
		int dm_m = max(s1, s2, 0, s->size_j);
		
		int** m = build_cost_matrix(j1, j2, s1, s2, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);
		//printf("---------sum: %d (%f)\n\n", sum, best->f_obj);
		if(OBJ(best->f_obj, sum)){
			s_line = generate_new_solution(f,dm_m,j1, j2, s1, s2, m, s->size_j);
			//printf("sum: %d (%f)\n\n", sum, best->f_obj);

			#ifdef DEBUG_OP
				printPcr(thread_id, PCR_BS_F, K[i], s_line->f_obj, best->f_obj, sum);
			#endif

			freeSolution(best);
			free(best);
			best = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
		}
		//free structs
		free(j2);		
		freeCostMatrix(m, dm_m);
		free(f);
	}
	
	free(K);
	#ifdef CALCULE_COST
		calculeCostFunction(best);
	#endif

	freeSolution(s);
	free(s);
	return best;
}


Solution* pcr_best_improvement_backward(Solution* s, int k, int thread_id){
	Solution* best = copySolution(s);
	int* K = generate_cut_places(best->j);
	Solution* s_line;
	int s1 = 0, s2 = 0;

	for (int i = LAYERS_SIZE-1; i >= 0; i--){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0;
		cut(s->j, s->size_j, K[i], j1, j2, &s1, &s2);
		int dm_m = max(s1, s2, 0, s->size_j);
		
		int** m = build_cost_matrix(j1, j2, s1, s2, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);
		//printf("---------sum: %d (%f)\n\n", sum, best->f_obj);
		if(OBJ(best->f_obj, sum)){
			s_line = generate_new_solution(f,dm_m,j1, j2, s1, s2, m, s->size_j);
			//printf("sum: %d (%f)\n\n", sum, best->f_obj);

			//free s
			#ifdef DEBUG_OP
				printPcr(thread_id, PCR_BS_B, K[i], s_line->f_obj, best->f_obj, sum);
			#endif

			freeSolution(best);
			free(best);
			best = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
		}
		//free structs
		free(j2);		
		freeCostMatrix(m, dm_m);
		free(f);
	}
	
	free(K);

	#ifdef CALCULE_COST
		calculeCostFunction(best);
	#endif

	freeSolution(s);
	free(s);
	return best;
}

/*************************************************************PCR CONTINUOUS IMPROVEMENT*******************************************************************************************************
*****************************************************************************************************************************************************************************************/
Solution* pcr_continuous_improvement_foward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	Solution* s_line;
	int s1 = 0, s2 = 0;

	for (int i = 0; i < LAYERS_SIZE; i++){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0;
		cut(s->j, s->size_j, K[i], j1, j2, &s1, &s2);
		int dm_m = max(s1, s2, 0, s->size_j);
		
		int** m = build_cost_matrix(j1, j2, s1, s2, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);

		if(OBJ(s->f_obj, sum)){
			s_line = generate_new_solution(f,dm_m,j1, j2, s1, s2, m, s->size_j);
			//printf("sum: %d (%f)\n\n", sum, s->f_obj);

			#ifdef DEBUG_OP
				printPcr(thread_id, PCR_CN_F, K[i], s_line->f_obj, s->f_obj, sum);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
		}
		//free structs
		free(j2);		
		freeCostMatrix(m, dm_m);
		free(f);
		//break;
	}
	
	free(K);
	#ifdef CALCULE_COST
		calculeCostFunction(s);
	#endif

	return s;
}


Solution* pcr_continuous_improvement_backward(Solution* s, int k, int thread_id){
	int* K = generate_cut_places();
	Solution* s_line;
	int s1 = 0, s2 = 0;

	for (int i = LAYERS_SIZE-1; i >= 0; i--){
		Journey** j1 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		Journey** j2 = (Journey**) calloc(s->size_j, sizeof(Journey*));
		s1 = 0, s2 = 0;
		cut(s->j, s->size_j, K[i], j1, j2, &s1, &s2);
		/*printf("::::::::::: J1 %d\n", s1);
		for (int i = 0; i < s1; i++){
			if(j1[i] != NULL){
				printJourney(&j1[i], NULL);
				printf("obj: %f\n\n", j1[i]->_obj);
			}
		}
		printf("::::::::::: J2 %d\n", s2);
		for (int i = 0; i < s2; i++){
			if(j2[i] != NULL){
				printJourney(&j2[i], NULL);
				printf("obj: %f\n\n", j2[i]->_obj);
			}
		}*/

		int dm_m = max(s1, s2, 0, s->size_j);
		
		int** m = build_cost_matrix(j1, j2, s1, s2, dm_m);
		//printMatrix(m, dm_m);
		//PA
		int z_p = 0; double sum = 0.0;
		int *f = (int*) calloc(dm_m, sizeof(int));
		apc(dm_m, m, MAX_INF, &z_p, f, &sum);
		//printVector(f, dm_m);
		//printResultVectorAPC(f, m, dm_m);
		//printf("PCR_CN_B -- s: %f; s': %d (%d) (%d)\n", s->f_obj, sum, (s->f_obj > sum), sum < s->f_obj);	
		if(OBJ(s->f_obj, sum) == 1){
			s_line = generate_new_solution(f,dm_m,j1, j2, s1, s2, m, s->size_j);
			//printf("--- sum: %d (s': %f)\n\n", sum, s_line->f_obj);

			#ifdef DEBUG_OP
				printPcr(thread_id, PCR_CN_B, K[i], s_line->f_obj, s->f_obj, sum);
			#endif

			freeSolution(s);
			free(s);
			s = s_line;
		}else{
			freeJourneys(j1, s->size_j);
			free(j1);
			freeJourneys(j2, s->size_j);
		}
		//free structs
		free(j2);		
		freeCostMatrix(m, dm_m);
		free(f);
		//break;
	}
	
	free(K);

	#ifdef CALCULE_COST
		calculeCostFunction(s);
	#endif

	return s;
}