#ifndef CONSTRUTIVE_PHASE_H
#define CONSTRUTIVE_PHASE_H

#include "readInstances.h"

#define DEFAULT_L 1000
int LAYERS_SIZE;

void printLayers(List** c);
void freeLayers(List** c);
int verifyViability(List* journey, Task* task);
Task* earlier_task(List* t);
int seq(List* layer, Task* new);
List** generate_layers(List* t);
List** generate_layers1(List* t);

#endif