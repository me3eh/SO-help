#include "read.h"
int main(int argc, char ** argv){
	//gdy chcemy tylko jeden plik akceptowac do wypisania
	/*if(argc != 2){
        	printf("Nieodpowiednia ilosc argumentow");
        	return 1;
    	}
    	*/
    	FILE * file;
    	if (argc == 1){
		printf("Podaj jakiekolwiek argumenty");
		return 1;
    	}
    	//sprawdzenie czy pliki istnieja. Jezeli chociaz jeden nie istnieje, podejmujemy akcje
    	for(int i = 1; i != argc;++i)
    		if(fopen(argv[i], "r") == NULL){
			printf("Jeden z plikow nie istnieje");
			return 1;
    		}
    	int i = 1;
    	while( i != argc){
        	file = fopen(argv[i],"r");
        	if(file == NULL){
            		printf("Wystapil blad z odczytem pliku");
            		return 1;
        	}
        	read_file(i, file);
        	++i;
        	fclose(file);
    	}
	return 0;
}
