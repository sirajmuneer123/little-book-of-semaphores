/*   No-starve readers-writers */
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex,r,w;
char input[1000];
int readers=0;
int k=10;
void *reader(void *a)
{
	while(1){	
	sem_wait(&r);
	sem_wait(&mutex);
	readers +=1;
	if(readers ==1)
		sem_wait(&w);
	sem_post(&mutex);
	sem_post(&r);
	//critical section for raders
	printf("Enter the input\n");
	scanf("%s",input);
	
	sem_wait(&mutex);
	readers -=1;
	if(readers == 0)
		sem_post(&w);
	sem_post(&mutex);
}
}
void *writer(void *a)
{
	while(1){
	sem_wait(&r);
	sem_wait(&w);
	//critical section for writer
	printf("%s\n",input);
	sem_post(&w);
	sem_post(&r);
}
}
main()
{
	pthread_t t1,t2;
	sem_init(&mutex,0,1);
	sem_init(&r,0,1);
	sem_init(&w,0,1);

	pthread_create(&t1,0,reader,0);
	pthread_create(&t2,0,writer,0);

	pthread_join(t1,0);
	pthread_join(t2,0);
	while(1);
}
