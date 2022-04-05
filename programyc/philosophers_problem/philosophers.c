#include <stdio.h> 
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NO_OF_PHILOSOPHERS 5

pthread_t philosophers[NO_OF_PHILOSOPHERS];
pthread_mutex_t mutex_forks[NO_OF_PHILOSOPHERS];
unsigned int count[NO_OF_PHILOSOPHERS];

void sig_handler(int signum){
    for(int j = 0 ; j < 5 ; ++j)
        printf("\n%d => %d", j, count[j]);
    exit(EXIT_SUCCESS);
}
void init(int * a)
{
    int i;
    for(i = 0; i<NO_OF_PHILOSOPHERS; i++){
        pthread_mutex_init(&mutex_forks[i], NULL);
        count[i] = 0;
        a[i] = i;
    }
}
void *philosopher(void* i)
{
    int left = (*(int*)i);
    int right = ((*(int*)i)+1)%5;
    while(1){
        pthread_mutex_lock(&mutex_forks[left]);
        pthread_mutex_lock(&mutex_forks[right]);
        ++count[left];
        printf("%d", left);
        pthread_mutex_unlock(&mutex_forks[right]);
        pthread_mutex_unlock(&mutex_forks[left]);
    }
    pthread_exit(NULL);
        
}

int main()
{
    srand(time(NULL));
    signal(SIGINT, sig_handler);
    int a[NO_OF_PHILOSOPHERS];
    init(a);
    int i;

    for(i = 0; i < NO_OF_PHILOSOPHERS ; i++)
        pthread_create( &philosophers[i], NULL, &philosopher, &a[i]);

    for(i = 0 ; i < NO_OF_PHILOSOPHERS ; i++)
        pthread_join(philosophers[i],NULL);
    return 0;
}