#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define n 5  //the number of threads
sem_t mutex,barrier;
int count = 0;
void *thread(void *a)
{
	sem_wait(&mutex);
	count = count +1;
	sem_post(&mutex);
	if(count == n)
		sem_post(&barrier);
	sem_wait(&barrier);
	sem_post(&barrier);
	
	printf("thread %d is in critical sectiom\n",*(int *)a);
}
main()
{
	int i;

	pthread_t t[n];
	sem_init(&mutex,0,1);
	sem_init(&barrier,0,0);
	
	for(i=0;i<n;i++)
		pthread_create(&t[i],0,thread,&i);
	for(i=0;i<n;i++)
		pthread_join(t[i],0);
	printf("count is : %d\n",count);

}
