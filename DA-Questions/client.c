#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num1, num2;
    char op;

    while (1) {
        printf("Enter two integers and an operator (+ or -): ");
        if (scanf("%d %d %c", &num1, &num2, &op) != 3) {
            fprintf(stderr, "Invalid input. Please enter two integers and an operator.\n");
            while (getchar() != '\n'); 
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            char num1_str[12], num2_str[12], op_str[2];
            snprintf(num1_str, sizeof(num1_str), "%d", num1);
            snprintf(num2_str, sizeof(num2_str), "%d", num2);
            snprintf(op_str, sizeof(op_str), "%c", op);

            execl("./server", "server", num1_str, num2_str, op_str, NULL);
            perror("execl failed");
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                int result = WEXITSTATUS(status);
                printf("Result: %d\n", result);
            } else {
                printf("Server process did not exit successfully.\n");
            }
        }
    }

    return 0;
}
