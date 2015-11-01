/*
Signaling.
*/
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX 1000
char line[MAX];
sem_t sem;
void *readLine(void *a)
{
	printf("\nEnter the line: ");
	scanf("%s",line);
	sem_post(&sem);

}
void *printLine(void *a)
{
	sem_wait(&sem);
	printf("The line is : ");
	printf("%s\n\n",line);

}
main()
{
	pthread_t t1,t2;
	sem_init(&sem,0,0);
	
	pthread_create(&t1,0,readLine,0);
	pthread_create(&t2,0,printLine,0);
	
	pthread_join(t1,0);
	pthread_join(t2,0); 
	
}
