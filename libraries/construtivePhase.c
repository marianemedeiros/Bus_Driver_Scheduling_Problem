#include "construtivePhase.h"

void printLayers(List** c){
	for (int i = 0; i < LAYERS_SIZE; i++) {
		printf("C%d\n", i);
		showDateTime(c[i]->first->data->start_time);
		printf("\n");
		showDateTime(c[i]->last->data->start_time);
		//printList(c[i], 0 , 0, NULL);
		printf("\n");
	}
}

void freeLayers(List** c){
	for (int i = 0; i < LAYERS_SIZE; i++) {
		freeList(c[i]); // nao precisa dar freeList pq como ja dei o freeJourney as tarefas ja foram desalocadas.
		//free(c[i]);
	}
	free(c);
}

int verifyViability(List* journey, Task* task){
	int rt = 0;
	//if(journey->size == 0)
	//	rt = 1;

	if(journey->last->data->destination == task->origin && compareDateTime(journey->last->data->end_time, task->start_time))
		rt = 1;
	
	return rt;
}

Task* earlier_task(List* t){
	Task* rt = inicializeTask();
	setTask(t->first->data, rt);
	removeList(t, 0);
	return rt;
}

int seq(List* layer, Task* new){
		Node* aux = layer->first;
		while (aux != NULL) {
			Task* last_element = aux->data;
			if((last_element->destination == new->origin) && compareDateTime(last_element->end_time, new->start_time))
				return 1;
			//else if((new->destination == last_element->origin) && compareDateTime(new->end_time, last_element->start_time))
			//	return 2;
			aux = aux->next;
		}
	return 0;
}

//version equal to Allanclair
List** generate_layers(List* t){
	//create a layer vector - each element of vector is a task list
	List** layers = (List**) calloc(DEFAULT_L, sizeof(List*));
	int index_layers = 0; // K <-0

	while(t->size >= 1) {
		Task* tp = earlier_task(t);
		int i = index_layers;

		while (i > 0 && seq(layers[i-1], tp) == 0){
			i--;
		}

	  	if(i == index_layers){
		    layers[index_layers] = initializeList();;
		    index_layers++;
		}
		addLastList(layers[i],tp);
		//else if(can_seq == 2)
		//	addLastList(layers[i],layers[i-1]->last->data);
	}

	LAYERS_SIZE = index_layers;
	layers = (List**) realloc(layers, LAYERS_SIZE* sizeof(List*));

	return layers;
}

//tasks of a same layer are sequential.
List** generate_layers1(List* t){
	//create a layer vector - each element of vector is a task list
	List** layers = (List**) calloc(DEFAULT_L, sizeof(List*));
	int index_layers = 0; // K <-0
	List* layer = initializeList();
	layers[index_layers] = layer;
	index_layers++;

	while(t->size >= 1) {
		Task* tp = earlier_task(t);
		int i = index_layers;

		if((i-1) == 0 && layers[i-1]->size == 0){// first task of first layer
		  addLastList(layers[i-1],tp);
		}else{
		  while (i > 0 && seq(layers[i-1], tp) == 0) {
		    i--;
		  }
		  if(i == 0){
		    layer = initializeList();
		    layers[index_layers] = layer;
				addLastList(layers[index_layers],tp);
		    index_layers++;
		  }else
		  	addLastList(layers[i-1],tp);
		}
	}

	return layers;
}
