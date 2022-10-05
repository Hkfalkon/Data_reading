
// header definitions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include "data.h"
#include "linkedlist.h"

//CONSTANT define

#define STAGE_ONE 49 // ascii number of 1
#define CSV_ARGMNT 2
#define OUTPUT_ARGMNT 3



int main(int argc, char *argv[]) {
    // read the file
    FILE* csv_file = fopen(argv[CSV_ARGMNT], "r");
    assert(csv_file);

    FILE* output_file = fopen(argv[OUTPUT_ARGMNT], "w");
    assert(output_file);

    //skip the header
    citySkipHeaderLine(csv_file);

    //try to loop and read the file until the end of file
    
    if (*argv[1] == STAGE_ONE) { //when stage1
        city_t *tempCity = NULL;
        list_t *list1 = listCreate();
        while((tempCity = cityRead(csv_file)) != NULL){
            //some linkedlist function, return headNode
            listAppend(list1, tempCity);        
        }
        // get matached address and return it if it is true, return NOTFOUND if not.
        char address[MAX_SIZE+1];
        int match;
        node_t *curr = NULL;
        curr = getHeadNode(list1);
        while((scanf("%[^\n]\n", address)) == 1) {
            //printf("Ran once!\n");
            fprintf(output_file, "%s\n", address);
            match = 0;
            while (curr) {
                //printf("add: %s\n", address);
                //printf("getadd: %s\n", getAddress(getCityNode(curr)));
                //printf("----------\n");
                // check if same address
                if(strcmp(address, getAddress(getCityNode(curr))) == 0) {
                    cityPrint(output_file, getCityNode(curr));
                    match++;
                }
                curr = getNextNode(curr);
            }
            if (match == 0) {
                printf("%s --> NOTFOUND\n", address);
            }
            else {
                printf("%s --> %d\n", address, match);
            }
            curr = getHeadNode(list1);
        }

        freelist(list1);
    } else {
    // Driver code for stage 2

        city_t *tempCity = NULL;
        // build empty array
        array_t *arr = NULL;
        arr = arrayCreate(arr);

        while((tempCity = cityRead(csv_file)) != NULL){
            //some linkedlist function, return headNode
            arrayAppend(arr, put_node(tempCity));
        }

        insertionSort(arr);
        double record;
        char *record_string = (char *)malloc(sizeof(char)*20);
        node_t *result_node;

        while((scanf("%[^\n]\n", record_string)) == 1) {
            //printf("Ran\n once!\n");
            /*to print the decimal floating-point values*/
            fprintf(output_file, "%s\n", record_string);
            record = atof(record_string);
            result_node = findClosest(arr, record);
            cityPrint(output_file, getCityNode(result_node));
            printf("%s --> %lf\n", record_string, node_get_grade1in(result_node));
        }
        //arrayFree(arr);
    }
    fclose(csv_file);
    fclose(output_file);
    return 0;
    
}
 
