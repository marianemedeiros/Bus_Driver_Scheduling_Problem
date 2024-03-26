#ifndef DOUBLY_LINKED_DYNAMIC_LIST_H
#define DOUBLY_LINKED_DYNAMIC_LIST_H

#include "task.h"

#define ItemType Task*



typedef struct node{
	ItemType data;
	struct node* prev;
	struct node* next;
}Node;

typedef struct{
	Node* first;
	Node* last;
	int size;
}List;

List* initializeList();
void addLastList(List* list, ItemType element);
void addList(List* list, ItemType element, int index);
int removeList(List* list, int index);
int removeElementList(List* list, ItemType element);
int removeLastElement(List* list);
int getList(List* list, ItemType* element, int index);
int setList(List* list, ItemType element, int index);
int indexOfList(List* list, ItemType element);
int containsList(List* list, ItemType element);
int sizeList(List* list);
int isEmptyList(List* list);
void printList(List* list, int j_key, int d, FILE* f);
List* copyList(List** list, List** newList);
List* copyListFromTo(List** list, List** newList, Node* from, int to, int free_);
ItemType getElementByIndex(List* list, int index);
Node* getNodeByIndex(List* list, int index);
void freeList(List* list);
void invertList(List* list);

#endif