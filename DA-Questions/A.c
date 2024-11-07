#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>



int main(){
    __pid_t pidB ;

    pidB = fork();

    if(pidB<0){
        printf("Cannot start process B\n");
        exit(1);
    }
    if(pidB==0){
        printf("Process B: Executing Program X...\n");
        execl("./X", "X", NULL);
        perror("execl failed\n");
        exit(1);
    }

    wait(NULL);
    printf("process A: child process B has been completed\n");
    return 0;
}