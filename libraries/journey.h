#ifndef JOURNEY_H
#define JOURNEY_H

#include "construtivePhase.h"
#include "vector.h"


#define NIGHT_FACTOR 1.2

#define MAX_CONT 360 // 6h

#define MIN_BREAK 90 
#define MAX_BREAK 300
#define MAX_JOURNEY 780 // 13h

#define MIN_HEXT 440 // 7:20h (tempo normal de horas trabalhadas)
#define MAX_HEXT 560 //9:20h (tempo máximo de horas extras trabalhadas)
#define HEXT_FACTOR 1.5

//#define MAX_INF 999999999
#define MAX_INF 9999999

typedef int bool;
#define TRUE  1
#define FALSE 0

typedef struct taskPair{
	List* l1;
	List* l2;
}TaskPair;

typedef struct journey{
	List* tasks;
	int key;
	double breakTime;
	bool maxBreak;
	int minBreak;
	int changeLine;
	int continuum;
	bool maxJourney;
	bool hext1;
	bool hext2;
	double _cost;
	double _obj;
	int duration;
	int realDuration;
	double (*function_to_buildMatrix)(struct journey* journey);
	double (*obj_function)(struct journey* journey);
	double (*cost_function)(struct journey* journey);
}Journey;

double g_and_obj1(Journey* journey);
double cost1(Journey* journey);
double obj1(Journey* journey);

Journey** reorganizeJourneys(Journey** j, Journey** j1, int size_j, int s_j1);
Journey** add_journey(int* journey_list_size, Journey* new_journey, Journey** journey_list);
void joinTwoJourneysAndObj(Journey* j1, Journey* j2, int* cost);
int joinJourneys(Journey* j1, Journey* j2);
void justJoinJourneys(Journey* j1, Journey* j2);
void disJoinJourneys(Journey* j1, Journey* j2, Node* j1_last, Node* j2_first);
void freeJourneys(Journey** j, int size);
void freeJourney(Journey* j);
double* drivingAndIdleTime(Journey* journey);
Journey* inicializeJourney();
TaskPair* zip(List* tasks);
int feasible(Journey* j);
Journey** copyJourneySet(Journey** journeys_set, int index_journeys_set, int new_size);
void printJourney(Journey** j, FILE* f);
Journey* copyJourney(Journey** from, Journey** to);
void cost(Journey* j);
void obj(Journey* journey);

#endif