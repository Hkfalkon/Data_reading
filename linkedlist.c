
// header definitions

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include "data.h"
#include "linkedlist.h"

/*  --------- strongly inspired by workshop4.7. -------------*/

//a list node
struct node {
    city_t *info;
    node_t *next;
};

// a linked list is defined as a couple of pointers
struct list {
	node_t *head;  // points to the first node of the list
	node_t *tail;  // points to the last node of the list 
};

// crate linkedlist and return head
node_t *createdLinkedList() {
    node_t *head = malloc(sizeof(node_t));
	return head;
};

// creates & returns an empty linked list
list_t *listCreate() {
	list_t *list = malloc(sizeof(*list));
	assert(list);
	list->head = list->tail = NULL;
	//list->n = 0;
	return list;
}


// free the list 
void freelist(list_t* list1) {
   node_t *tmp = list1->head;
   node_t *prenode;
   while (tmp != NULL) {
	   free_city(tmp->info);
	   prenode = tmp;
       tmp = tmp->next;
	   free(prenode);
	}
	free(list1);
}


// inserts a new node with value "data" to the end of "list" 
void listAppend(list_t *list, void *data) {
	assert(list);

	// creates a new node and set data 
	node_t *new = malloc(sizeof(*new));
	assert(new);
	new->info = data;
	new->next = NULL;

	//head node is null
	if (list->head == NULL) {
		list->head = new;
	}
	//tail node is null, head node adress next
	else if (list->tail == NULL) {
		list->tail = new;
		list->head->next = new;
	}
	//check new tail node
	else {
		//list->tail->next connect to the new node
		list->tail->next = new;
		//reference the tail attribute to new node
		list->tail = new;
	}
}

// return head node
node_t *getHeadNode(list_t *tempList) {
	return tempList->head;
}

// return tail node
node_t *getTailNode(list_t *tempList) {
	return tempList->tail;
}

// return city data node
city_t *getCityNode(node_t *tempNode) {
	return tempNode->info;
}

// return next city node
node_t *getNextNode(node_t *tempNode) {
	return tempNode->next;
}

// return grade1in with node
double node_get_grade1in(node_t *node) {
	return getGrade1in(node->info);
}

// make a space and return node
node_t *put_node(city_t *s) {
	node_t *node = NULL;
	node = (node_t*)malloc(sizeof(*node));
	node->info = s;
	node->next = NULL;
	return node;
}

// return how many 
int getLength(node_t *head) {
	node_t *curr = head;
	int count = 0;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}

/* ---------- Strongly inspired by workshop3.9 questions ---------- */
struct array {
	node_t **A;      // use as array of student_t *, ie. student_t *A[]
	int size;           // current array size
	int n;              // current number of elements
};

// creates & returns an empty array
array_t *arrayCreate() {
	array_t *arr = malloc(sizeof(*arr));
	assert(arr);
	int size = INIT_SIZE;      // "size" used for convenience
	arr->size = size;
	arr->A = malloc(size * sizeof(*(arr->A)));
	assert(arr->A);
	arr->n = 0;
	return arr;
}

// free memory used by array "arr"
// void arrayFree(array_t *arr) {
// 	for (int i = 0; i < arr->n; i++) {
// 		studentFree(arr->A[i]);
// 	}
// 	free(arr->A);
// 	free(arr);
// }

// makes sure that array's size exceeds its number of elements
//    ie. there is space for adding new element
void arrayEnableInsert(array_t *arr) {
	if (arr->n == arr->size) {
		arr->size <<= 1;       // same as arr->size *= 2;
		arr->A= realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}

// inserts/appends data "s" to the end of array "arr" 
void arrayAppend(array_t *arr, node_t *s) {
	arrayEnableInsert(arr);
	arr->A[arr->n] = s;
	(arr->n)++;
}


// /* ---- inspired by https://www.geeksforgeeks.org/find-closest-number-array/  ----- */
 
// Returns element closest to target in arr[]
node_t *findClosest(array_t *arr, double target) {

    // binary search
    int low = 0, high = arr->n - 1, mid = 0;
	double min_dis = DBL_MAX;
	node_t *result;
    while (low <= high) {
        mid = (low + high) / 2;
        if (node_get_grade1in(arr->A[mid]) == target) {
            result = arr->A[mid];
			break;
        }
 
        /* If target is less than array element, then search in left */
        else if (target < node_get_grade1in(arr->A[mid])) {
            // If target is greater than previous to mid, return closest of two
			if (min_dis > fabs(node_get_grade1in(arr->A[mid]) - target)) {
				min_dis = fabs(node_get_grade1in(arr->A[mid]) - target);
				result = arr->A[mid];
			}
		
            high = mid - 1;
        }

        /* Repeat for left half */
        // If target is greater than mid
        else {
            if (min_dis > fabs(node_get_grade1in(arr->A[mid]) - target)) {
				min_dis = fabs(node_get_grade1in(arr->A[mid]) - target);
				result = arr->A[mid];
			}
            // update i
            low = mid + 1;
        }
    }
    // Only single element left after search
    return result;
}



// Insertion sort in C
// Function to print an array
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void insertionSort(array_t *arr) {
	int n = arr->n;
	int j;
	double key;
	node_t *current;
    for (int step = 1; step < n; step++) {
        key = node_get_grade1in(arr->A[step]);
		current = arr->A[step];
        j = step - 1;

        // Compare key with each element on the left of it until an element smaller than it is found.
        // For descending order, change key<array[j] to key>array[j].
        while ((j >= 0) && (key < node_get_grade1in(arr->A[j]))) {
            arr->A[j + 1] = arr->A[j];
            j--;
        }
		arr->A[j + 1] = current;
    }
}





