// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

void* thread(void* arg)
{
	//wait
	// sem_wait(&mutex);
	printf("\nEntered..%d\n", *(int*)arg);

	//critical section
	sleep(4);
	
	//signal
	printf("\nJust Exiting...%d\n", *(int*)arg);
	// sem_post(&mutex);
}


int main()
{
	sem_init(&mutex, 0, 1);

	pthread_t t1,t2, t3;
	int a = 2, b = 1, c = 3;
	pthread_create(&t1,NULL,thread, &b);
	// sleep(2);
	pthread_create(&t2,NULL,thread, &a);
	pthread_create(&t3, NULL, thread, &c);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3, NULL);
	sem_destroy(&mutex);
	return 0;
}
