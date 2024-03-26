#ifndef READ_INSTANCES_H
#define READ_INSTANCES_H

#include<string.h>
#include "doublyLinkedDynamicList.h"
#include "threads/files.h"

#define H_M 60
#define LINE_FEED 10
#define ENTER 13

int NUMBER_TASKS;
List* TASK_LIST;
Task** task_vector;
int index_task_vector;

void freeTaskVector();

/*read each line of file and convert that in a Task*/
Task* readLine(char* line);

/*read file*/
List* readFile(char* url);

#endif


