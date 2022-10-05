
// header definition
#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>
typedef struct city city_t;
#include "linkedlist.h"

// constant defnitions
#define LEN_DATASET 19
#define MAX_SIZE 128
#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512

// data definitions

/*------------ function definitions -----------------------------*/

// skip the header line of .csv file "f"
void citySkipHeaderLine(FILE *f);

// reads a student from file "f" to build a student_t data
// returns the pointer, or NULL if reading is unsuccessful
city_t *cityRead(FILE *f);

// prints the header line for the list of students
//void studentPrintHeader(FILE *f);

// prints a student record *s to file "f"
void cityPrint(FILE *f, city_t *s);

// print the how many city information matched
void lengthPrint(node_t *s);

// return address data through city data
char *getAddress(city_t *info);

// return grade1in data
double getGrade1in(city_t *info);

// print following output to stdout
void lengthPrint(node_t *s);

// free char data in city datas
void free_city(city_t *data);

#endif

