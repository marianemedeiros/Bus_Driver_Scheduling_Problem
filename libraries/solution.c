#include "solution.h"

#define INF 9999999

void printSolution(Solution* s, FILE* f){
	if(s->size_j > 0){
		for (int i = 0; i < s->size_j; i++) {
			
			if(s->j[i] != NULL){
				printJourney(&s->j[i], f);
			}
		}
	}else
		fprintf(f, "Jornada vazia\n");
}

void writeSolution_dot(Solution* s, char* name){
   FILE *fp =  openFile(name, "w");

   fprintf(fp, "graph g {\nranksep=0.2;\noverlap=scale;\n");
   
   for (int i = 0; i < s->size_j; i++){
   		Node* aux = s->j[i]->tasks->first;
   		fprintf(fp, "\"J%d\" -- \"%d (%d-%d) (%c-%c)\" [style=dotted];\n", s->j[i]->key, aux->data->key, aux->data->start_time->hours2minutes, aux->data->end_time->hours2minutes, aux->data->origin, aux->data->destination);
		while(aux->next != NULL){
			fprintf(fp, "\"%d (%d-%d) (%c-%c)\" -- \"%d (%d-%d) (%c-%c)\" [weight=1.2, len=0.5];\n", 
				aux->data->key, aux->data->start_time->hours2minutes, aux->data->end_time->hours2minutes, aux->data->origin, aux->data->destination,  
				aux->next->data->key, aux->data->start_time->hours2minutes, aux->data->end_time->hours2minutes, aux->next->data->origin, aux->next->data->destination);
			aux = aux->next;
		}
		//fprintf(fp, "\"%d (%d-%d) (%s-%s)\" -- \"%f\" [weight=1.2, len=0.5];\n", aux->data->key, aux->data->st_min, aux->data->et_min, aux->data->origin, aux->data->destination, s->j[i]->_cost);
   }
   fprintf(fp, "}");
   fclose(fp);
}

void freeSolution(Solution* s){
	if(s->j == NULL)
		printf("Trying <<free>> a NULL list of journey...\n");
	
	freeJourneys(s->j, s->size_j);
	free(s->j);
}

Solution* copySolution(Solution* c){
	if(c->j == NULL)
		printf("Trying <<copy>> a NULL list of journey...\n");
	
	Solution* rt = inicializeSolution(c->size_j);

	for (int i = 0; i < c->size_j; i++){
		rt->j[i] = inicializeJourney(1);

		if(c->j == NULL)
			printf("vetor J é null %d\n", i);

		rt->j[i] = copyJourney(&c->j[i], &rt->j[i]);
	}
	rt->f_obj = c->f_obj;
	rt->f_cost = c->f_cost;
	rt->duration = c->duration;
	return rt;
}

int equalSolutions(Solution* s1, Solution* s2){
	int rt = 1;
	if(s1->size_j != s2->size_j){
		printf("Diferent sizes of journeys (s1: %d, s2: %d).\n", s1->size_j, s2->size_j);
		return 0;
	}
	else{
		for (int i = 0; i < s1->size_j; i++) {
			Node* next1 = s1->j[i]->tasks->first;
			Node* next2 = s2->j[i]->tasks->first;
			if(s1->j[i]->tasks->size != s2->j[i]->tasks->size){
				printf("Diferent sizes of tasks (s1->j[%d]: %d, s2->j[%d]: %d).\n", i, s1->j[i]->tasks->size, i, s2->j[i]->tasks->size);
				printf("T1:::\n");
				printList(s1->j[i]->tasks, i, 0, NULL);
				printf("T2:::\n");
				printList(s2->j[i]->tasks, i, 0, NULL);
				return 0;
			}
			else{
				while(next1 != NULL){
					if(!equalTasks(next1->data, next2->data)){
						printf("Tasks Not Equals (t1: %d, t2: %d).\n", next1->data->key, next2->data->key);
						printf("T1:::\n");
						printTask(next1->data, i, 0, NULL);
						printf("T2:::\n");
						printTask(next2->data, i, 0 ,NULL);
						return 0;
					}
					next1 = next1->next;
					next2 = next2->next;
				}
			}
		}
	}
	return rt;
}

void addTask2Journey(Task* task, List* j_tasks, int key){
	addLastList(j_tasks, task);
	task->journey_key = key;
}

double g(Journey* journey, Task* task){
	Task* c_task = inicializeTask();
	c_task = copyTask(&task, &c_task);

	Journey* j = inicializeJourney(1);
	j = copyJourney(&journey, &j);

	if(task->journey_key == -1)
		addLastList(j->tasks, c_task);
 	
	double cost = j->function_to_buildMatrix(j);
	freeJourney(j);
	free(j);
	return cost;
}

int** buildCostMatrix(Journey** journeys, List* layer, int* index_journeys_set){
	//int index_journeys = 0;
	int cnj = 440; //7h20min, cost of a journey
	int n, len_jor, len_layer;
	n = *index_journeys_set + layer->size;
	len_jor = *index_journeys_set;
	len_layer = layer->size;
	//printf("len_jor: %d; len_l: %d; \n n: %d\n", len_jor, len_layer, n);
	int** cost_matrix = (int**) calloc(n, sizeof(int*));
	//printf("len_jor:: %d; len_layer: %d; n: %d\n", len_jor, len_layer, n);

	for (int jor  = 0;  jor < n; jor++) {
		cost_matrix[jor] = (int*) calloc(n, sizeof(int));

		for (int t  = 0;  t < n; t++) {
			cost_matrix[jor][t] = MAX_INF;// inicialize cost matrix

			if(jor < len_jor && t < len_layer){ // block 1
				//printf("bloco 1\n");
				Journey* j = journeys[jor];
				Task* task = getElementByIndex(layer,t);
				//printf("j:: %d, t::%d\n", jor, t);
				//printTask(j->tasks->last->data, 0, 0, NULL);
				//printf("X\n");
				//printTask(task, 0, 0, NULL);
				//printf("-----------------\n\n");
				int aux = verifyViability(j->tasks, task);
				//printf("%d -- %d\n", j->tasks->last->data->end_time->hours2minutes, task->start_time->hours2minutes);
				if(aux == 1){//verifica se há viabilidade para alocar a tarefa task na jornada journey->tasks
					int aux =  g(j, task);//se sim: faz calculo para verificar o custo da jornada.
					cost_matrix[jor][t] = aux;
					//printf("(%d) Viabilidade de atribuição. Novo size: %d\n", jor, j->tasks->size);
				}
			}//end block 1

			else if(jor < len_jor && t < n){ // block 2
				//printf("bloco 2\n");
				if(feasible(journeys[jor])){
					//journeys[jor]->obj_function(journeys[jor]);
					//cost_matrix[jor][t] = journeys[jor]->_obj;
					//journeys[jor]->_obj = -1;
					cost_matrix[jor][t] = journeys[jor]->function_to_buildMatrix(journeys[jor]);
				}
			}//end block 2

			else if(jor < n && t < len_layer){ // block 3
				//printf("bloco 3: %d::%d\n", jor, t);
				if(cost_matrix[(jor-len_jor)][t] >= MAX_INF)
					cost_matrix[jor][t] = cnj;
			}//end block 3

			else{ // block 4
				//printf("bloco 4\n");
				cost_matrix[jor][t] = 0;
				//printf("(bloco 4 - %d)", cost_matrix[jor][t]);
			}

		}//end t
		//printf("\n");
	}//end jor
	//printMatrix(cost_matrix, n);
	//printf("\n");
	return cost_matrix;
}

Journey** transformMatrix(int* f, int size, List* layer, Journey** journeys_set, int* index_journeys_set){
	if(journeys_set == NULL){
		journeys_set = (Journey**) calloc(size, sizeof(Journey*));
	}else{
		int t = (*index_journeys_set) + (size - (*index_journeys_set));
		journeys_set = copyJourneySet(journeys_set, (*index_journeys_set), t);
		size = t;
	}

	for (int i = 0; i < size; i++) {
		int i_t1 = f[i]; // index of task

		if(i_t1 < layer->size){
			Task* o_t = getElementByIndex(layer, i_t1);

			if(o_t->end_time->hours2minutes > min_end_time)
				min_end_time = o_t->end_time->hours2minutes;

			Task* t = inicializeTask();
			t = copyTask(&o_t, &t);
			if(i < (*index_journeys_set) && verifyViability(journeys_set[i]->tasks,t)){
				//printf("Adiciona tarefa em uma jornada já existente (%d) (index: %d).\n", i, *index_journeys_set);
				addTask2Journey(t, journeys_set[i]->tasks, journeys_set[i]->key);
			}else{
				journeys_set[*index_journeys_set] = inicializeJourney(1);
				journeys_set[*index_journeys_set]->key = *index_journeys_set;
				//printf("journey key: %d (index: %d)\n", journeys_set[*index_journeys_set]->key, *index_journeys_set);
				addTask2Journey(t, journeys_set[*index_journeys_set]->tasks, journeys_set[*index_journeys_set]->key);
				(*index_journeys_set)++;
			}
		}
	}
	return journeys_set;
}

int calculate_duration(Journey* j){
	Node* t = j->tasks->last;
	double rt = 0;
	if(j->tasks->size == 1){
		double* l = lenTransformation(t->data->start_time->hours2minutes, t->data->end_time->hours2minutes, t->data->duration);
		rt = (int) (l[0] + l[1]);
		free(l);
		//return (int) (l[0] + l[1]);
	}else{
		while(t->prev != NULL){

			double* l = lenTransformation(t->data->start_time->hours2minutes, t->data->end_time->hours2minutes, t->data->duration);
			rt += l[0] + l[1];
			Task* t_prev = t->prev->data;
			free(l);
			
			int hours2minutes_aux = verifyToAddDay(t->data->start_time->hours2minutes, t_prev->end_time->hours2minutes);
			//printf("hours2minutes_aux: %d -- %d\n", hours2minutes_aux, t->data->start_time->hours2minutes);
			rt += (double) hours2minutes_aux - t_prev->end_time->hours2minutes;
			t = t->prev;
		}
		double* l = lenTransformation(t->data->start_time->hours2minutes, t->data->end_time->hours2minutes, t->data->duration);
		rt += (int) (l[0] + l[1]);
		free(l);
	}
	return (int) rt;	
}

void calculeDuration(Solution* s){
	for (int i = 0; i < s->size_j; i++) {
		s->j[i]->duration = calculate_duration(s->j[i]);
		s->duration += s->j[i]->duration;
	}
}


void calculeObjectiveFunction(Solution* s){
	fo_count++;
	s->f_obj = 0;
	for (int i = 0; i < s->size_j; i++) {
		s->j[i]->_obj = s->j[i]->obj_function(s->j[i]);
		s->f_obj += s->j[i]->_obj;
	}
}

void calculeCostFunction(Solution* s){
	s->f_cost = 0;
	for (int i = 0; i < s->size_j; i++) {
		s->j[i]->_cost = s->j[i]->cost_function(s->j[i]);
		s->f_cost += s->j[i]->_cost;
	}
}

void calculeCostAndObjective(Solution* s){
	for (int i = 0; i < s->size_j; i++) {
		s->j[i]->_cost = s->j[i]->cost_function(s->j[i]);
		s->j[i]->_obj = s->j[i]->obj_function(s->j[i]);

		s->f_cost += s->j[i]->_cost;
		s->f_obj += s->j[i]->_obj;
	}
}

Solution* initialSolution(List** layers){
	Solution* s = inicializeSolution(-1);
	min_start_time = layers[0]->first->data->start_time->hours2minutes;

	for (int i = 0; i < LAYERS_SIZE; i++) {// iterates over layers
		//printf("Layer %d <<<<<<\n", i);
		//printList(layers[i], 0,0,NULL);
		//printf(">>>>>>\n");
		int** m = buildCostMatrix(s->j, layers[i], &s->size_j); // passa a camada e uma jornada vazia

		int z_p = 0; double sum = 0.0;
		int size = s->size_j + layers[i]->size;

		int *f = (int*) calloc(size, sizeof(int));
		apc(size,m,INF, &z_p, f, &sum);
		s->j = transformMatrix(f,size,layers[i], s->j, &s->size_j);
		//desalocar matriz de custo
		for (int i = 0; i < size; i++) {
			free(m[i]);
		}
		free(f);
		free(m);
	}
 	calculeCostAndObjective(s);
 	calculeDuration(s);
	return s;
}

Solution* inicializeSolution(int instantiate_journey){
	Solution* s = (Solution*) calloc(1, sizeof(Solution));

	if(instantiate_journey != -1){
		s->j = (Journey**) calloc(instantiate_journey, sizeof(Journey*));
		s->size_j = instantiate_journey;
	}
	else{
		s->j = NULL;
		s->size_j = 0;
	}
	s->f_obj = 0.0;
	s->f_cost = 0.0;
	s->duration = 0.0;
	return s;
}