#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define N 5

sem_t forks[N];

void *philosopher(void *num){
    int id = *((int *)num);
    while(1){
        //Think
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand()%3+1);
        
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up left fork.\n", id);

        sem_wait(&forks[(id+1)%N]);
        printf("Philosopher %d picked  up right fork.\n", id);

        // Eat
        sleep(rand()%3+1);

        // put down right fork
        sem_post(&forks[(id+1)%N]);
        printf("Philosopher %d put down up right fork.\n", id);

        // put down left fork
        sem_post(&forks[id]);
        printf("Philosopher %d put down left fork.\n", id);

    }
}


int main()
{
    pthread_t philosophers[N];
    int philosophers_ids[N];

    for(int i=0;i<N;i++)
    {
        sem_init(&forks[i],0,1);
    }

    for(int i=0;i<N;i++){
        philosophers_ids[i] =i;
        pthread_create(&philosophers[i],NULL,philosopher,&philosophers_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (not reached in this case)
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;

}