#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex,roomEmpty;
char input[1000];
int readers=0;
void *reader(void *a)
{
	while(1){
		sem_wait(&mutex);
		readers +=1;
		if(readers ==1)
			sem_wait(&roomEmpty);
		sem_post(&mutex);

		//critical section for raders
		printf("Enter the input\n");
	
		scanf("%s",input);
		sem_wait(&mutex);
		readers -=1;
		if(readers == 0)
			sem_post(&roomEmpty);
		sem_post(&mutex);
	}

}
void *writer(void *a)
{
	
	sem_wait(&roomEmpty);
	
	//critical section for writer
	printf("%s\n",input);
	
	sem_post(&roomEmpty);
}
main()
{
	pthread_t t1,t2;
	sem_init(&mutex,0,1);
	sem_init(&roomEmpty,0,1);

	pthread_create(&t1,0,reader,0);
	pthread_create(&t2,0,writer,0);

	pthread_join(t1,0);
	pthread_join(t2,0);
//	while(1);
}
