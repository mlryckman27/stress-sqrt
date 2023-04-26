#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while (1) {
        // Get user input
        char cmd[100];
        printf("> ");
        fgets(cmd, 100, stdin);

        // Remove newline character from input
        cmd[strcspn(cmd, "\n")] = '\0';

        // Check if user entered "exit" command
        if (strcmp(cmd, "exit") == 0) {
            exit(0);
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            char *args[] = {"worker", cmd, NULL};
            execv("./worker", args);
            printf("Failed to execute worker\n");
            exit(1);
        } else {
            // Parent process
            int status;

            // Loop until child process exits
            while (waitpid(pid, &status, WNOHANG) == 0) {
                // Get user input
                char newcmd[100];
                printf("> ");
                fgets(newcmd, 100, stdin);

                // Remove newline character from input
                newcmd[strcspn(newcmd, "\n")] = '\0';

                // Check if user entered "exit" command
                if (strcmp(newcmd, "exit") == 0) {
                    exit(0);
                }

                // Fork a new child process to run worker
                pid_t newpid = fork();

                if (newpid == 0) {
                    // Child process
                    char *newargs[] = {"worker", newcmd, NULL};
                    execv("./worker", newargs);
                    printf("Failed to execute worker\n");
                    exit(1);
                } else {
                    // Parent process
                    pid = newpid;
                }
            }
        }
    }

    return 0;
}
