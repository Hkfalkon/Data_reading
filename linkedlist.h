
// header definitions
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include <stdio.h>
typedef struct node node_t;
typedef struct list list_t;
typedef struct array array_t;
#include "data.h"

// constant defnitions
#define INIT_SIZE 2


/*------------ stage 1 function definitions -----------------------------*/

node_t *createdLinkedList();

list_t *listCreate();

void freelist(list_t* list1);

int listCount(list_t *list);

void listAppend(list_t *list, void *data);

node_t *getHeadNode(list_t *tempList);

node_t *getTailNode(list_t *tempList);

city_t *getCityNode(node_t *tempNode);

node_t *getNextNode(node_t *tempNode);

double node_get_grade1in(node_t *node);

node_t *put_node(city_t *s);

void arrayEnableInsert(array_t *arr);

int getLength(node_t *head);

/*------------ stage 2 function definitions -----------------------------*/

array_t *arrayCreate();

void arrayAppend(array_t *arr, node_t *s);

node_t *findClosest(array_t *arr, double target);

void printArray(int array[], int size);

void insertionSort(array_t *arr);

#endif

