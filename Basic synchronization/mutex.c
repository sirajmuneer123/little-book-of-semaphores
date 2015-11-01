#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
int count=0;
sem_t mutex;
void *threadA(void *a)
{
	sem_wait(&mutex);
//	critical section
	count = count + 1;
	sem_post(&mutex);
}
void *threadB(void *a)
{
	sem_wait(&mutex);
//	critical section
	count = count + 1;
	sem_post(&mutex);

}
main()
{
	pthread_t t1,t2;
	
	sem_init(&mutex,0,1);
	printf("Count before thread : %d\n",count);
	pthread_create(&t1,0,threadA,0);
	pthread_create(&t2,0,threadB,0);

	pthread_join(t1,0);
	pthread_join(t2,0);
	
	printf("count after thread : %d\n",count);
}
