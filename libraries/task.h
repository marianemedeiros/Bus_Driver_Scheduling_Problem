#ifndef TASKS_H
#define TASKS_H

#include <math.h>
#include "datetime.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define SIZE_LINE 5
#define ONE 2
int NUMBER_OF_TASKS;

typedef struct task{
	char bus_line[SIZE_LINE];
	char origin;
	char destination;
	int t_out;
	int m_out;
	int duration;
	int bus_number;
	int finish_h;
	int finish_m;

	DateTime* start_time;
	DateTime* end_time;

	int key;	
	int journey_key;
}Task;

/*Inicialize and create Task struct*/
Task* inicializeTask();

/*Print Task*/
void printTask(Task* t, int j_key, int duration, FILE* f);

/*Insert in task t, the informations contained in task newInfo*/
Task* setTask(Task* from, Task* to);

/*free memory of Task struct*/
void freeTask(Task* t);

/* Deep copy. Copy all elements of task 
* @param 'from' to task 
* @param 'to'
*/
Task* copyTask(Task** from, Task** to);

int equalTasks(Task* t1, Task* t2);

/*Verify limits of working times, how much hours are worked at day and nigth. 
* @param 'st' is a start time of a tast, 
* @param 'et' is a end time of task and len is duration of a task
*/
double* lenTransformation(int st, int et, int len);

/*Call lenTranformation
* @param current, Task struct
* @param next, Task struct
*/
double* gapDayNight(Task* current, Task* next);


double gap(Task* current, Task* next, int real);

#endif