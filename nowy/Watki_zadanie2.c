#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
int iteration = 0;
void *function( void * k );

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void main()
{
    int rc [10];
    pthread_t thread [10];
    srand((unsigned)time(NULL));

    int k=0;
    for(int i = 0 ; i < 10 ; ++i){
        void * retval;
        if( (rc[i]=pthread_create( &thread[i], NULL, &function, &k)) ){
            fprintf(stderr, "Thread creation failed: %d\n", rc[i]);
        }
        pthread_join(thread[i], &retval);
        if (retval == PTHREAD_CANCELED){
            printf("The thread was canceled - ");
            exit(EXIT_FAILURE);
        }
        k = *(int*)retval;
        ++iteration; 
    }
    printf("Ilosc wszystkich iteracji:%d", k);

    exit(EXIT_SUCCESS);
}

void *function( void * k ){
    
    int d = rand() %10000;
    void * da = k;
    printf("---------------------------------------------------------------------------\n");
    for( int i = 0 ; i < d; ++i ){
        pthread_mutex_lock( &mutex1 );
        ++(*( (int *) da));
        pthread_mutex_unlock( &mutex1 );
        if( i % 400 == 0)
            printf( "Watek %d iteracja %d \n", iteration, i );
    }
    printf("\b\b  \n");
    pthread_exit(da);
}