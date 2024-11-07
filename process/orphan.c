#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    __pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent process (PID: %d) exiting, creating an orphan child.\n", getpid());
        exit(0);  // Parent exits, child becomes orphan
    } 
    else if (pid == 0) {
        // Child process
        sleep(2); // Give the parent time to exit
        printf("Orphan child process (PID: %d) running with new parent PID: %d\n", getpid(), getppid());
        // Keep the orphan child alive for observation
        sleep(10); // Simulate some work
        printf("Orphan child process (PID: %d) exiting.\n", getpid());
    } 
    else {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
