#include "restriction_evaluator.h"

int verify_viability(Journey* j){
	Node* aux = j->tasks->first;
	int rt = 0;
	while(aux->next != NULL){
		Task* current = aux->data;
		Task* next = aux->next->data;
		
		if(current->destination != next->origin && !compareDateTime(current->end_time, next->start_time)){
			rt = 1;
			fprintf(debug, "%c - %c :: %d - %d ", current->destination, next->origin, current->end_time->hours2minutes, next->start_time->hours2minutes);
			printf("%c - %c :: %d - %d ", current->destination, next->origin, current->end_time->hours2minutes, next->start_time->hours2minutes);
		}
		aux = aux->next;
	}
	return rt;
}

void verify_restriction(Solution* s){
	for (int i = 0; i < s->size_j; i++) {
		double* aux = drivingAndIdleTime(s->j[i]);
		double totalTime = aux[4];


		//printf("Journey %d time is: %f. BreakTime: %f\n", s->j[i]->key, totalTime, s->j[i]->breakTime);
		
		if(totalTime > MAX_HEXT){ //restriction 2 (max time)
			printf(">>> i %d\n", i);
			printf("s key>> %d", s->j[i]->key);
			fprintf(debug, "R2 - Journey %d time (%f) exceeds the maximum working time (440 min).\n", s->j[i]->key, totalTime);
		}
		//restriction 4
		if(s->j[i]->continuum != 0)
			fprintf(debug, "R4 - Continumm Time: %d\n", s->j[i]->continuum);

		//restriction 5
		if (s->j[i]->continuum == 1 && s->j[i]->breakTime < 78 ){
			fprintf(debug, "R5.1 - minBreak: %d. BreakTime is %f and the mininum break time needs to be 1h 30m.\n", s->j[i]->minBreak, s->j[i]->breakTime);
		}

		if (s->j[i]->maxBreak){
			fprintf(debug, "R5.2 - maxBreak: %d. BreakTime is %f and maximum break time can be 5h.\n", s->j[i]->maxBreak, s->j[i]->breakTime);
		}
		
		
		//restriction 6
		if(verify_viability(s->j[i])){
			fprintf(debug, "(j %d) R6 violated\n", i);
			printf("(j %d) R6 violated\n", i);
		}

		//restriction 7
		if (totalTime + s->j[i]->breakTime > MAX_JOURNEY){
			fprintf(debug, "R7 - maximum extention of journey %d (%f)\n", s->j[i]->key, (totalTime + s->j[i]->breakTime));
		}
		//printf("\n");
		free(aux);
	}
}