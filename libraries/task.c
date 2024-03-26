#include "task.h"

void freeTask(Task* t){
	free(t->start_time);
	free(t->end_time);
	free(t);
}

void printTask(Task* t, int j_key, int duration, FILE* f){
	if(f == NULL)
		printf("%d %s %c %c %dd:%dh:%dm (%d) 0d:0h:%dm %dd:%dh:%dm (%d) %d %d\n", t->key, t->bus_line, t->origin, t->destination, 
		t->start_time->day, t->start_time->hour, t->start_time->minute, t->start_time->hours2minutes,
		t->duration, t->end_time->day, t->end_time->hour, t->end_time->minute, t->end_time->hours2minutes, duration, j_key);
	else
		//26  235   G  T  0:17:20  0d:0015  0:17:35  98  0
		fprintf(f, "%d %c %c %c %d:%d:%d 0d:00%d %d:%d:%d %d %d\n", t->key, t->bus_line[0],
		t->origin, t->destination, 
		t->start_time->day, t->start_time->hour, t->start_time->minute,
		t->duration, t->end_time->day, t->end_time->hour, t->end_time->minute, duration, j_key);
}

Task* copyTask(Task** from, Task** to){
	(*(*to)->bus_line) = (*(*from)->bus_line);
	(*to)->origin = (*from)->origin;
	(*to)->destination = (*from)->destination;
	(*to)->t_out = (*from)->t_out;
	(*to)->m_out = (*from)->m_out;
	(*to)->duration = (*from)->duration;
	(*to)->bus_number = (*from)->bus_number;
	(*to)->finish_h = (*from)->finish_h;
	(*to)->finish_m = (*from)->finish_m;

	(*(*to)->start_time) = (*(*from)->start_time);
	(*(*to)->end_time) = (*(*from)->end_time);

	(*to)->key = (*from)->key;
	(*to)->journey_key = (*from)->journey_key;
	return (*to);
}

int equalTasks(Task* t1, Task* t2){
	if(t1->key == t2->key)
		return 1;
	return 0;
}

Task* inicializeTask(){
	Task* t = (Task*) calloc(1,sizeof(Task));
	
	t->bus_line[0] = 'N';
	t->origin = 'N';
	t->destination = 'N';
	t->t_out = 0;
	t->m_out = 0;
	t->duration = 0;
	t->bus_number = 0;
	t->finish_h = 0;
	t->finish_m = 0;

	t->start_time = inicializeDateTime();
	t->end_time = inicializeDateTime();

	t->key = -1;
	t->journey_key = -1;
	return t;
}

Task* setTask(Task* from, Task* to){
	to->bus_line[0] = from->bus_line[0];
	to->origin = from->origin;
	to->destination = from->destination;
	to->t_out = from->t_out;
	to->m_out = from->m_out;
	to->duration = from->duration;
	to->bus_number = from->bus_number;
	to->finish_h = from->finish_h;
	to->finish_m = from->finish_m;
	to->start_time = setDateTime(from->start_time, to->start_time);
	to->end_time = setDateTime(from->end_time, to->end_time);

	to->key = from->key;
	to->journey_key = from->journey_key;
	return to;
}

double* lenTransformation(int s, int e, int len){
	//int s_a = verifyToAddDay(s, e);
	
	double st = (double) s;
	double et = (double) e;

	double NIGHT = 22*60; // night limits
	double MORNING = 5*60; // morning limits
	double DAY = 24*60; // day duration
	double FACTOR = 60/52.5; //change factor of time
	st = (int) st % (int) DAY;
	et = (int) et % (int) DAY;
	double lenDay = len;
	double lenNight = 0;

	if (st >= NIGHT && et >= NIGHT){ // 22 e 0h
			lenNight = lenDay*FACTOR;
			lenDay = 0;
	}
	else if (st >= NIGHT && et <= MORNING){ // passou das 0h
			lenNight = lenDay*FACTOR;
			lenDay = 0;
  	}
	else if (st <= MORNING && et <= MORNING){ // entre 0h e 5h
			lenNight = lenDay*FACTOR;
			lenDay = 0;
	}
	else if (st <= NIGHT && et >= NIGHT){
			lenDay = NIGHT - st;
			lenNight = (et - NIGHT)*FACTOR;
	}
	else if (st <= MORNING && et >= MORNING){
			lenNight = (MORNING - st)*FACTOR;
			lenDay = et - MORNING;
	}
	double* rt  = (double*) calloc(2, sizeof(double));
	rt[0] = lenDay;
	rt[1] = lenNight;

	return rt;
}

double* gapDayNight(Task* current, Task* next){
	int diff = 0;
	if(current->end_time->day == 0 && next->start_time->day == 1){
		diff = (next->start_time->hours2minutes + 1440) - current->end_time->hours2minutes;
	}else{
		diff = (next->start_time->hours2minutes - current->end_time->hours2minutes);
	}

	return lenTransformation(current->end_time->hours2minutes, next->start_time->hours2minutes, diff);
}

double gap(Task* current, Task* next, int real){
	int diff = 0;
	if(current->end_time->day == 0 && next->start_time->day == 1){
		diff = (next->start_time->hours2minutes + 1440) - current->end_time->hours2minutes;
	}else{
		diff = (next->start_time->hours2minutes - current->end_time->hours2minutes);
	}

	int st = current->end_time->hours2minutes;
	int et = next->start_time->hours2minutes;
	if (real == 0){
		double* aux_len = lenTransformation(st, et, diff);
		diff = aux_len[0] + aux_len[1];
		free(aux_len);
	}
	return diff;
}
