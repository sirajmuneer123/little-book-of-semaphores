#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX 1000
sem_t emptySlot,fullSlot;;
int buffer[MAX];
int head=0;
int tail=0;
int c=0;
int waitForEvet(void);
void *producer(void *a)
{
	int c=0;
	int event;
	while(1){
		event=waitForEvent();
		sem_wait(&emptySlot);
		buffer[head]=event;
		c++;
		head=(head+1)%1000;
		sem_post(&fullSlot);
	}
	
}
int waitForEvent(void)
{
	return c;
}
void *consumer(void *a)
{
	while(1){
		sem_wait(&fullSlot);
		printf("%d\n",buffer[tail]);
		tail=(tail+1) % 1000;
		sem_post(&emptySlot);
	}

}
main()
{
	pthread_t t1,t2;
	sem_init(&emptySlot,0,MAX);
	sem_init(&fullSlot,0,0);

	pthread_create(&t1,0,producer,0);
	pthread_create(&t2,0,consumer,0);
	
	pthread_join(t1,0);
	pthread_join(t2,0);
	

}
