#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFFER_SIZE 5


int buffer[BUFFER_SIZE];
int count =0;

sem_t empty;
sem_t full;
sem_t sem;

void *producer(void *arg){
    int i =0;
    while(1){
        // semaphore to become zero and not let any thread access the buffer, if any thread tries to access it make it 1 only if the buffer is not empty
        sem_wait(&empty);
        sem_wait(&sem);

        buffer[count++] = i;
        printf("Produced: %d\n",i++);

        sem_post(&sem);
        sem_post(&full);

        sleep(1);
    }
}


void *consumer(void *arg){
    while(1){
        sem_wait(&full);
        sem_wait(&sem);

        int item = buffer[--count];
        printf("Consumed: %d\n", item);

        sem_post(&sem);
        sem_post(&empty);

        sleep(1);
    }
}


int main(){
    pthread_t prod, cons;

    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    sem_init(&sem,0,1);

    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&sem);

    return 0;
}