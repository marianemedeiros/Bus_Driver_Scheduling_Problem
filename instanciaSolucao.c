#include "libraries/metaheuristics/gvns.h"

void preencheTask(Task* t, char bus_line, char origin, char destination, int duration, int bus_number, int key, int journey_key, 
	int day, int hour, int minute, int h2m, int e_day, int e_hour, int e_minute, int e_h2m){
	t->bus_line[0] = bus_line;
	t->origin[0] = origin;
	t->destination[0] = destination;
	t->t_out = 0;
	t->m_out = 0;
	t->duration = duration;
	t->bus_number = bus_number;
	t->finish_h = 0;
	t->finish_m = 0;

	t->start_time = inicializeDateTime();
	t->start_time->day = day;
	t->start_time->hour = hour;
	t->start_time->minute = minute;
	t->start_time->hours2minutes = h2m;

	t->end_time = inicializeDateTime();
	t->end_time->day = e_day;
	t->end_time->hour = e_hour;
	t->end_time->minute = e_minute;
	t->end_time->hours2minutes = e_h2m;

	t->key = key;
	t->journey_key = journey_key;
}

Solution* pcr_first_improvement_foward_teste(Solution* s){
		SolutionTuple* st = cut(s, 1320);

		//printf("SOLUÇÂO 1\n\n\n\n");
		//showJourneys(st->s1->j, st->s1->size_j, st->s1->f_obj);

		//printf("SOLUÇÂO 2\n\n\n\n");
		//showJourneys(st->s2->j, st->s2->size_j, st->s2->f_obj);

		int dm = st->max_size;
		int** m = build_cost_matrix(st->s1, st->s2, dm);
		
		for (int i = 0; i < dm; i++){
			for (int j = 0; j < dm; j++){
				printf("%d ", m[i][j]);
			}
			printf("\n");
		}

		//PA
		int z_p = 0;
		int *f = (int*) calloc(dm, sizeof(int));
		apc(dm,m,MY_INF, &z_p, f);

		for (int i = 0; i < dm; ++i){
			printf("%d ", f[i]);
		}
		
		Solution* s_line = generate_new_solution(m, f,dm,st->s1, st->s2);
		calculeCostFunction(s_line);
		//printf("---------------------------- obj function\n");
		//calculeObjectiveFunction(s_line);
		//showJourneys(s_line->j, s_line->size_j, s_line->f_obj);

		printf("obj: %f (z_p: %d)\n\n", s_line->f_obj, z_p);
		
		if(OBJ(s->f_obj, s_line->f_obj)){
			for (int j = 0; j < dm; j++){
				printf("%d ", f[j]);
			}
			//calculeObjectiveFunction(s_line);
			//calculeCostFunction(s_line);
			//calculeDuration(s_line);
			printf(" %d - F: z_p: %d (obj: %f); s atual: %f\n", 360, z_p, s_line->f_obj, s->f_obj);

			//free s
			//freeSolution(s);

			//free structs
			for (int i = 0; i < dm; i++) {
				free(m[i]);
			}
			free(m);
			free(f);
			return s_line;
		}
		
		//free structs
		freeSolution(st->s1);//só da free em s1 pois o generate_new_solution, junta s1 e s2.
		free(st->s1);
		free(st);
		for (int i = 0; i < dm; i++) {
			free(m[i]);
		}
		free(m);
		free(f);
	//}
	
	return s;
}

int main(){
	Task* t1 = inicializeTask();
	preencheTask(t1, 'A', 'T', 'T', 40, 123, 1, 1, 0, 6, 0, 360, 0, 6, 40, 400);

	Task* t2 = inicializeTask();
	preencheTask(t2, 'A', 'T', 'T', 30, 123, 2, 2, 0, 22, 0, 1320, 0, 22, 30, 1350);

	Task* t3 = inicializeTask();
	preencheTask(t3, 'A', 'T', 'T', 30, 123, 3, 1, 0, 22, 30, 1350, 0, 23, 0, 1380);

	Task* t4 = inicializeTask();
	preencheTask(t4, 'A', 'T', 'T', 10, 123, 4, 1, 0, 23, 0, 1380, 0, 23, 10, 1390);


	Journey* j1 = inicializeJourney(1);
	addLastList(j1->tasks,t1);
	addLastList(j1->tasks,t3);
	addLastList(j1->tasks,t4);

	Journey* j2 = inicializeJourney(1);
	addLastList(j2->tasks,t2);

	Solution *s = inicializeSolution(2);
	s->j[0] = j1;
	s->j[1] = j2;

	showJourneys(s->j, s->size_j, s->f_obj);
	calculeCostAndObjective(s);
	printf(ANSI_COLOR_RED "Initial Solution: \n --- Journeys size: %d \n --- Objective Function: %f \n --- Cost Funtion: %f\n --- Sched Duration: %f\n" ANSI_COLOR_RESET, s->size_j, s->f_obj, s->f_cost, s->duration);

	Solution* x = pcr_first_improvement_foward_teste(s);
	showJourneys(x->j, x->size_j, x->f_obj);

	printf(ANSI_COLOR_RED "Initial Solution: \n --- Journeys size: %d \n --- Objective Function: %f \n --- Cost Funtion: %f\n --- Sched Duration: %f\n" ANSI_COLOR_RESET, x->size_j, x->f_obj, x->f_cost, x->duration);
}