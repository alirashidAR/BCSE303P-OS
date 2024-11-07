#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent process (PID: %d) created a child process (PID: %d).\n", getpid(), pid);
        printf("Parent process sleeping to keep child as a zombie...\n");
        sleep(10); // Keep the parent alive while child becomes a zombie
        printf("Parent process waking up and calling wait() to clean up the zombie.\n");
        wait(NULL); // Clean up the zombie process
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) exiting.\n", getpid());
        exit(0); // Child exits, becoming a zombie as parent hasn't called wait() yet
    } 
    else {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
