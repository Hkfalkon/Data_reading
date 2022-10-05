#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char* getfield(char* line, int num) {
    const char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

int main() {
    FILE* stream = fopen("dataset_2.csv", "r");

	if (stream == NULL) {
		printf( "Could not open source file\n" );
    	exit(1);
	}
    char line[1024];
    while (fgets(line, sizeof(line), stream)) {

		char *token;
		token = strtok(line, ",");

		while (token != NULL){
			printf("%s", token);
			token = strtok(NULL, ",");
		}
		printf("\n");

    }
}