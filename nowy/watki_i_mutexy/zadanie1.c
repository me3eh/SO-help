#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *functionC(void * how_much);
unsigned int counter = 0;
// volatile unsigned int counter = 0;

int main(int argc, char ** argv)
{
    if(argc != 3){
        printf("Nieodpowiednia ilosc argumentow");
        exit(EXIT_FAILURE);
    }
    char*lil_buffa;
    int N = (int)strtol(argv[1],&lil_buffa, 10);
    int ITER = (int)strtol(argv[2], &lil_buffa, 10);
    if (N <= 0 || ITER <= 0){
        printf("Argumenty nie moga byc mniejsze/rowne 0");
        exit(EXIT_FAILURE);
    }

    int rc[N];
    pthread_t thread[N];
    for(int i=0 ; i < N ; ++i){
        if( (rc[i] = pthread_create( &thread[i], NULL, &functionC, &ITER ) ) ){
            printf("Thread creation failed: %d\n", rc[i]);
            return -1;
        }
    }
    for(int t = 0; t < N ; ++t){
        pthread_join( thread[t], NULL);
    }
    printf("\n\n%d\n", counter);
    exit(EXIT_SUCCESS);
}

void *functionC(void * how_much)
{
    for(int j=0;j<*(int*)how_much;++j){
        pthread_mutex_lock( &mutex1 );
        ++counter;
        pthread_mutex_unlock( &mutex1 );
    }
    pthread_exit(how_much);
}