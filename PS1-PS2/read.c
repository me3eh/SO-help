#include "read.h"
int read_file(int i, FILE * file){
    	char line [255];
    	printf("Zawartosc %d pliku\n", i);
    	printf("------------------\n");
    	while(fgets(line, sizeof(line), file))
        	printf("%s", line);
    	printf("\n\n\n\n");
    	return 0;
}
