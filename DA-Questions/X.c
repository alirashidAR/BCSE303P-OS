#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){
    __pid_t pidY, pidZ;
    pidY = fork();

    if(pidY<0){
        printf("Error creating process Y\n");
        exit(1);
    }
    if(pidY==0){
        printf("Creating Process Y, taking input\n");
        sleep(10);
        getchar();
        exit(0);
    }

    pidZ = fork();
    if(pidZ<0){
        printf("Error creating process Z\n");
        exit(1);
    }
    if(pidZ==0)
    {
        printf("Created process Z\n");
        printf("Printing Helllooo World\n");
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Both processes have been completed.\n");
}