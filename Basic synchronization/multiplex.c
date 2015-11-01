/* multiplex.  */
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define N 100
#define CN 10
sem_t multiplex;
int count =0;
void *threadN(void *a)
{
	sem_wait(&multiplex);
	int semValue;
	sem_getvalue(&multiplex,&semValue);
	printf("Thread is : %d  and   semVlaue is : %d\n",*(int *)a,semValue);
	count +=1;
	sem_post(&multiplex);
}
main()
{
	int i;
	pthread_t t[N];
	sem_init(&multiplex,0,CN);
	printf("count before : %d\n",count);
	for(i=0;i<N;i++)
		pthread_create(&t[i],0,threadN,&i);
	for(i=0;i<N;i++)
		pthread_join(t[i],0);
	printf("count after : %d\n\n",count);

}
