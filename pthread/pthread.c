#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int g_val = 0;
sem_t lock;
void* thread_run(void *arg)
{
	while(1)
	{
		sem_wait(&lock);
		printf("A");
		fflush(stdout);
		sleep(1);
		printf("A");
		fflush(stdout);
		sem_post(&lock);
	}
}

int main(int argc, char const *argv[])
{
	sem_init(&lock,0,1);

	pthread_t id;
	pthread_create(&id,NULL,thread_run,NULL);
	while(1)
	{
		sleep(1);
		sem_wait(&lock);
		printf("B");
		sleep(1);
		fflush(stdout);
		printf("B");
		fflush(stdout);
		sem_post(&lock);
	}
	pthread_join(id,NULL);
	printf("main thread done...");

	return 0;
}