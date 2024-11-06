#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

sem_t rw_mutex;
sem_t mutex;
int read_count =0;
int data =0;


void *reader(void *arg)
{
    int id =*(int*)arg;
    while(1){

        sem_wait(&mutex);
        read_count++;
        if(read_count==1){
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        printf("Reader %d: Read data = %id\n",id,data);
        sleep(1);

        //exit
        sem_wait(&mutex);
        read_count--;
        if(read_count==0){
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        sleep(1);
    }

    return NULL;
}


void *writer(void *arg)
{
    int id = *(int*)arg;

    while(1){
        sem_wait(&rw_mutex);

        data+=10;
        printf("Writer %d: Wrote data = %d\n",id,data);
        sleep(1);

        sem_post(&rw_mutex);

        sleep(1);
    }

    return NULL;
}



int main(){
    pthread_t r_threads[5], w_threads[2];
    int r_ids[5], w_ids[2];

    sem_init(&rw_mutex,0,1);
    sem_init(&mutex,0,1);

    for(int i=0;i<5;i++){
        r_ids[i]=i+1;
        pthread_create(&r_threads[i],NULL,reader,&r_ids[1]);
    }

    for(int i=0;i<2;i++){
        w_ids[i]=i+1;
        pthread_create(&w_threads[i],NULL,writer,&w_ids[i]);
    }

    for(int i=0;i<5;i++)
    {
        pthread_join(r_threads[i],NULL);
    }

    for(int i=0;i<2;i++)
    {
        pthread_join(r_threads[i],NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

}
