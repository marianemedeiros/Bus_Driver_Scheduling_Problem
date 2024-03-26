#ifndef SOLUTION_H
#define SOLUTION_H

#include "journey.h"
#include "PA/apc.h"

int fo_count;
int min_start_time;
int min_end_time;


typedef struct solution{
	Journey** j;
	int size_j;
	double f_obj;
	double f_cost;
	double duration;

}Solution;

Solution* inicializeSolution(int instantiate_journey);

void printSolution(Solution* s, FILE* f);
void writeSolution_dot(Solution* s, char* name);
void freeSolution(Solution* s);
Solution* copySolution(Solution* c);
int equalSolutions(Solution* s1, Solution* s2);
double g(Journey* journey, Task* task);
int** buildCostMatrix(Journey** journeys, List* layer, int* index_journeys_set);
Solution* initialSolution(List** layers);
void calculeObjectiveFunction(Solution* s);
void calculeCostFunction(Solution* s);
void calculeDuration(Solution* s);	//calculeDuration sempre calculado depois do cost, pois o calculeCostFunction zera o duration.

#endif