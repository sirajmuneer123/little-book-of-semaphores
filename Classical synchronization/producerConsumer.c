#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define BUF_MAX 100

sem_t mutex, items, spaces;

int evtIndex=0;
int head=0,tail=0;
int buffer[BUF_MAX];
int eventBuf[] = {1,2,3,4,5,6,7,8,9,10};
int eventNum = sizeof(eventBuf) / sizeof(int);

void *producer(void *a);
void *consumer(void *a);
int waitForEvent(void);
int get(int buffer[]);
void process(int event);
void add(int buffer[],int  event);

void *producer(void *a)
{
    int event;

    while(1){
        event = waitForEvent();

        sem_wait(&spaces);
        sem_wait(&mutex);
            add(buffer, event);
        sem_post(&mutex);
        sem_post(&items);
    }
}
void *consumer(void *a)
{
    int event;

    while(1){
        sem_wait(&items);
        sem_wait(&mutex);
            event = get(buffer);
        sem_post(&mutex);
        sem_post(&spaces);

        process(event);
    }
}

int get(int buffer[])
{
    return buffer[tail++ % BUF_MAX];
}

void process(int event)
{
    printf("event%d\n", event);
}

int waitForEvent(void)
{
    return eventBuf[evtIndex++ % eventNum];
}

void add(int buffer[], int event)
{
    buffer[head++ % BUF_MAX] = event;
}
main()
{
    pthread_t t1, t2;

    sem_init(&mutex, 0, 1);
    sem_init(&items, 0, 0);
    sem_init(&spaces, 0, BUF_MAX);

    pthread_create(&t1, 0, consumer, 0);
    pthread_create(&t2, 0, producer, 0);

    while(1);
}
