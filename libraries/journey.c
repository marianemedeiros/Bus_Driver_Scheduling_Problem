#include "journey.h"

void printJourney(Journey** j, FILE* f){
	if((*j)->tasks != NULL)
		printList((*j)->tasks, (*j)->key, (*j)->realDuration, f);
}

void freeJourneys(Journey** j, int size){
	for (int i = 0; i < size; i++) {
		if(j[i] != NULL){
			freeJourney(j[i]);
		}else{
			//printf("aqioooooooo %d\n", i);
		}
		free(j[i]);
	}
}

void freeJourney(Journey* j){
	if(j->tasks != NULL)
		freeList(j->tasks);
}

Journey* copyJourney(Journey** from, Journey** to){
	(*to)->tasks = copyList(&(*from)->tasks, &(*to)->tasks);
	(*to)->key = (*from)->key;
	(*to)->breakTime = (*from)->breakTime;
	(*to)->maxBreak = (*from)->maxBreak;
	(*to)->minBreak = (*from)->minBreak;
	(*to)->changeLine = (*from)->changeLine;
	(*to)->continuum = (*from)->continuum;
	(*to)->maxJourney = (*from)->maxJourney;
	(*to)->hext1 = (*from)->hext1;
	(*to)->hext2 = (*from)->hext2;
	(*to)->_cost = (*from)->_cost;
	(*to)->_obj = (*from)->_obj;
	(*to)->duration = (*from)->duration;
	(*to)->realDuration = (*from)->realDuration;
	return (*to);
}

Journey** copyJourneySet(Journey** journeys_set, int index_journeys_set, int new_size){
	Journey** new_js = (Journey**) calloc(new_size, sizeof(Journey*));

	for (int i = 0; i < new_size; i++) {
		if(i < index_journeys_set){
			new_js[i] = inicializeJourney(1);
			new_js[i] = copyJourney(&journeys_set[i], &new_js[i]);
			freeJourney(journeys_set[i]);
			free(journeys_set[i]);
		}
	}
	free(journeys_set);
	return new_js;
}

void reset(Journey* journey){
		journey->minBreak = 0;
		journey->maxBreak = FALSE;
		journey->breakTime = 0;
		journey->changeLine = 0;
		journey->continuum = 0;
		journey->maxJourney = FALSE;
		journey->hext1 = FALSE;
		journey->hext2 = FALSE;
		journey->duration = 0;
}

Journey** reorganizeJourneys(Journey** j, Journey** j1, int size_j, int s_j1){
	j = (Journey**) calloc(s_j1, sizeof(Journey*));
	int index_j = 0;
	for (int i = 0; i < size_j; i++){
		if(j1[i] != NULL){
			j[index_j] = j1[i];
			index_j++;
		}else{
			free(j1[i]);
		}
	}
	free(j1);
	return j;
}

Journey** add_journey(int* journey_list_size, Journey* new_journey, Journey** journey_list){
	journey_list = (Journey**) realloc(journey_list, (*journey_list_size+1)* sizeof(Journey*));
	journey_list[*journey_list_size] = new_journey;
	journey_list[*journey_list_size]->key = *journey_list_size;	
	(*journey_list_size)++;
	return journey_list;
}

void joinTwoJourneysAndObj(Journey* j1, Journey* j2, int* cost){
	if(j2 != NULL){
		if(verifyViability(j1->tasks, j2->tasks->first->data)){
			j1->tasks->last->next = j2->tasks->first;
			j1->tasks->size += j2->tasks->size;
			*cost = j1->obj_function(j1);
			//printJourney(&j1, NULL);		
			
			j1->tasks->size -= j2->tasks->size;
			j1->tasks->last->next = NULL;
		}else{
			//printJourney(&j1, NULL);
			//printJourney(&j2, NULL);
			//*cost = MAX_INF;
			*cost = j1->obj_function(j1);
			*cost += j2->obj_function(j2);	
		}
	}
	else if (j2 == NULL){
		//j1->obj_function(j1);
		*cost = j1->_obj;
		//printJourney(&j1, NULL);
		//j1->_obj = -1;
	}
}

void disJoinJourneys(Journey* j1, Journey* j2, Node* j1_last, Node* j2_first){
	j1->tasks->last->next = NULL;
	j2->tasks->first->prev = NULL;
	j1->tasks->last = j1_last;
	j2->tasks->first = j2_first;

	j2->tasks->first->prev = NULL;
	j1->tasks->last->next = NULL;
}

void justJoinJourneys(Journey* j1, Journey* j2){
	j1->tasks->last->next = j2->tasks->first;
	j2->tasks->first->prev = j1->tasks->last;
	j1->tasks->last = j2->tasks->last;
	j2->tasks->first = j1->tasks->first;

	j2->tasks->first->prev = NULL;
	j1->tasks->last->next = NULL;
}


int joinJourneys(Journey* j1, Journey* j2){
	if(verifyViability(j1->tasks, j2->tasks->first->data)){
		j1->tasks->last->next = j2->tasks->first;
	    j2->tasks->first->prev = j1->tasks->last;
	    j1->tasks->last = j2->tasks->last;
	    j2->tasks->first = j1->tasks->first;

	    j2->tasks->first->prev = NULL;
	    j1->tasks->last->next = NULL;
	    return 1;
	}
	return 0;
}

int feasible(Journey* j){
	return j->hext2 == FALSE && j->maxJourney == FALSE && j->continuum == 0 && j->maxBreak == FALSE;
}

int extraHour(int total){
	return (total - MIN_HEXT)*HEXT_FACTOR;
}

TaskPair* zip(List* tasks){
	List* l1 = initializeList();
	Node* aux1 = tasks->first->next;
	l1 = copyListFromTo(&tasks,&l1,aux1,tasks->size, 0);

	List* l2 = initializeList();
	l2 = copyListFromTo(&tasks,&l2,tasks->first, tasks->size-1, 0);

	TaskPair* taskpair = (TaskPair*) calloc(1,sizeof(TaskPair));
	taskpair->l1 = l1;
	taskpair->l2 = l2;

	return taskpair;
}

double* drivingAndIdleTime(Journey* journey){
	double* rt = (double*) calloc(6, sizeof(double));
	double drivingTimeDay = 0.0, drivingTimeNight = 0.0, idleTimeDay = 0.0, idleTimeNight = 0.0, totalTime = 0.0, idleTime = 0.0, continuumTime = 0.0;
	reset(journey);
	TaskPair* tp = zip(journey->tasks);
	if((tp->l1->size > 0 && tp->l2->size > 0) || journey->tasks->size >= 1){
		double* x = lenTransformation(journey->tasks->first->data->start_time->hours2minutes, journey->tasks->first->data->end_time->hours2minutes, journey->tasks->first->data->duration);
		drivingTimeDay = x[0];
		drivingTimeNight = x[1];
		//printf("drivingTimeDay: %d, drivingTimeNight: %d\n", drivingTimeDay, drivingTimeNight);
		totalTime = x[0] + x[1];
		continuumTime = totalTime;
		free(x);
	}else{
		//int drivingTimeDay, drivingTimeNight = 0;
		drivingTimeDay = 0.0; drivingTimeNight = 0.0; totalTime = 0.0;
		continuumTime = 0.0;
	}
	idleTime = 0.0 ,idleTimeDay = 0.0 ,idleTimeNight = 0.0;

	//scroll through TaskPair
	Node* next = tp->l1->first;//next
	Node* current = tp->l2->first;//current
	while(next != NULL && current != NULL){
		double* dTime = lenTransformation(next->data->start_time->hours2minutes, next->data->end_time->hours2minutes, next->data->duration);
		drivingTimeDay += dTime[0];
		drivingTimeNight += dTime[1];

		//printf("<<<<<<<< %d, %d, %d, %d >>>>>>>>>>>\n", next->data->et_min, next->data->st_min, current->data->st_min ,current->data->et_min);
		double* auxGap = gapDayNight(current->data, next->data);
		double idle = auxGap[0] + auxGap[1];
		//printf("!!!!!!!! idle: %f (%f - %f)\n", idle, auxGap[0] ,auxGap[1]);
		double gapR = gap(current->data, next->data,1);
		//printf("gapR: %f\n", gapR);
		if( gapR >= MIN_BREAK){
			journey->minBreak += 1; // tempo minimo de descanso encontrado
			continuumTime = 0.0; // reset continuumTime
			idle = 0.0;
			journey->breakTime += gapR;
			//printf("journey->breakTime: %f (gapR: %f)\n", journey->breakTime, gapR);
			if(gapR > MAX_BREAK)
				journey->maxBreak = TRUE;
			//printf("j->breakTime: %f , maxBreak: %f\n", journey->breakTime, journey->maxBreak);
		}
		else if(idle >= 0.0 && idle < MIN_BREAK){ // real idle time
			idleTimeDay += auxGap[0];
			idleTimeNight += auxGap[1];
			idleTime += idleTimeDay + idleTimeNight;
			continuumTime += dTime[0] + dTime[1] + idle; // idle time pago + len pago
		}
		if (continuumTime > MAX_CONT)
    		journey->continuum += 1;
    	if ((*current->data->bus_line) != (*next->data->bus_line))
      			journey->changeLine += 1;

		totalTime += dTime[0] + dTime[1] + idle;
	 	 //printf("%d:%d - totalTime: %d, dTime: %d, idle: %d\n", current->data->key, next->data->key, totalTime, (dTime[0]+dTime[1]), idle);
		free(auxGap);
		free(dTime);

		next = next->next;
		current = current->next;
	}
	rt[0] = drivingTimeDay;
	rt[1] = drivingTimeNight;
	rt[2] = idleTimeDay;
	rt[3] = idleTimeNight;
	rt[4] = totalTime;
	rt[5] = idleTime;
	freeList(tp->l1);
	freeList(tp->l2);
	free(tp);
	//printf("drivingTimeDay - %d (0), drivingTimeNight - %d (1), idleTimeDay - %d (2), idleTimeNight - %d (3), totalTime - %d (4), idleTime - %d (5)\n", rt[0], rt[1], rt[2], rt[3], rt[4], rt[5]);
	//drivingTimeDay - 0, drivingTimeNight - 1, idleTimeDay - 2, idleTimeNight - 3, totalTime - 4, idleTime - 5
return rt;
}


Journey* inicializeJourney(){
	Journey* rt = (Journey*) calloc(1,sizeof(Journey));
	rt->function_to_buildMatrix = g_and_obj1;
	rt->obj_function = obj1;
	rt->cost_function = cost1;

	rt->tasks = initializeList();

	rt->key = -1;
	rt->breakTime = 0;
	rt->maxBreak = FALSE;
	rt->minBreak = 0;
	rt->changeLine = 0;
	rt->continuum = 0;
	rt->maxJourney = FALSE;
	rt->hext1 = FALSE;
	rt->hext2 = FALSE;
	rt->_cost = -1.0;
	rt->_obj = -1.0;
	rt->duration = 0;
	rt->realDuration = 0;
	return rt;
}

/**************************************************************************** EVALUATION FUNCTIONS ****************************************************************************/

/*
this function is used to calculate cost of a journey at build cost matrix.
*/
double g_and_obj1(Journey* journey){
	double* aux = drivingAndIdleTime(journey);
	//printf("drivingTimeDay - %f (0), drivingTimeNight - %f (1), idleTimeDay - %f (2), idleTimeNight - %f (3), totalTime - %f (4), idleTime - %f (5)\n", aux[0], aux[1], aux[2], aux[3], aux[4], aux[5]);
	double drivingTimeDay = aux[0], drivingTimeNight = aux[1], idleTimeDay = aux[2], idleTimeNight = aux[3], totalTime = aux[4];// idleTime = aux[5];
	double obj = drivingTimeDay + drivingTimeNight*NIGHT_FACTOR + idleTimeDay + idleTimeNight*NIGHT_FACTOR;
	//printf("obj cost_to_start_journey: %f (totalTime: %f)\n", obj, totalTime);
	if (totalTime > MAX_HEXT){
		//printf("IF1\n");
		journey->hext2 = TRUE;
		obj += MAX_INF; //PHEMAX
	}else if (totalTime > MIN_HEXT){// calcula o custo de ter dado essa hora extra
		//printf("IF2\n");
		journey->hext1 = TRUE;
		obj += extraHour(totalTime);
	}
	//printf("pra entrar no if3: %f, %f\n", totalTime , journey->breakTime);
	if (totalTime + journey->breakTime > MAX_JOURNEY){
		//printf("IF3\n");
		journey->maxJourney = TRUE;
		obj += MAX_INF; //PJM
	}
	if (journey->continuum != 0){
		//printf("IF4\n");
		obj += MAX_INF;
	}
	if (journey->maxBreak){
		//printf("IF5\n");
		obj += MAX_INF;
	}
	//printf("----------------end of cost_to_start_journey-------------\n");
	 free(aux);
	 //printf("obj: %f\n", obj);
	return obj;
}

double cost1(Journey* journey){
	//if(journey->_cost == -1){
		double* aux = drivingAndIdleTime(journey);
		//printf("drivingTimeDay - %f (0), drivingTimeNight - %f (1), idleTimeDay - %f (2), idleTimeNight - %f (3), totalTime - %f (4), idleTime - %f (5)\n", aux[0], aux[1], aux[2], aux[3], aux[4], aux[5]);
		double drivingTimeDay = aux[0], drivingTimeNight = aux[1], idleTimeDay = aux[2], idleTimeNight = aux[3], totalTime = aux[4]; //idleTime = aux[5];
		double cost = drivingTimeDay + drivingTimeNight*NIGHT_FACTOR + idleTimeDay + idleTimeNight*NIGHT_FACTOR;
		journey->realDuration = cost;
		if (totalTime > MIN_HEXT)
			cost += extraHour(totalTime);
		if(cost < MIN_HEXT){
			cost = MIN_HEXT;
		}
		//printf("Cost: %f \n\n", journey->_cost);
		free(aux);
		return cost;
	//}
}

double obj1(Journey* journey){
	//if(journey->_obj == -1){
		double* aux = drivingAndIdleTime(journey);
		double drivingTimeDay = aux[0], drivingTimeNight = aux[1], idleTimeDay = aux[2], idleTimeNight = aux[3], totalTime = aux[4]; //idleTime = aux[5];
		double obj = drivingTimeDay + drivingTimeNight*NIGHT_FACTOR + idleTimeDay + idleTimeNight*NIGHT_FACTOR;
		//printf("totalTime: %f; obj: %f\n", totalTime, obj);
		if (totalTime > MAX_HEXT){
			journey->hext2 = TRUE;
			obj += MAX_INF; //PHEMAX
			//printf("IF1: %f\n", obj);
		}else if (totalTime > MIN_HEXT){
			journey->hext1 = TRUE;
			obj += extraHour(totalTime);
			//printf("IF2:  %f\n", obj);
		}
		if (totalTime + journey->breakTime > MAX_JOURNEY){
			journey->maxJourney = TRUE;
			obj += MAX_INF; //PJM
			//printf("IF2: %f\n", obj);
		}
		if (journey->continuum != 0){
			obj += MAX_INF;
			//printf("IF3: %f\n", obj);
		}
		if (journey->maxBreak){
			obj += MAX_INF;
			//printf("IF4: %f\n", obj);
		}
		if(obj < MIN_HEXT){
			obj = MIN_HEXT;
		}
		free(aux);
		return obj;
	//}
}

