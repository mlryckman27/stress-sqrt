#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv) {

    char* prompt[] = {"Enter CPU number to start, 'exit' to quit: "};

    while (1) {

        // Get user input
        char workerArgs[100];
        printf("%s", prompt[0]);
        fgets(workerArgs, 100, stdin);
        workerArgs[strcspn(workerArgs, "\n")] = '\0';

        // Exit application if 'exit' is specified
        if (strcmp(workerArgs, "exit") == 0) {
            printf("Exiting...\n");
            kill(0, SIGTERM);
            exit(0);
        }

        // Fork child process
        pid_t pid = fork();

        // Handle behavior for parent, child, or failure to fork child
        if (pid < 0) {
            printf("Fork failed: %d\n", pid);
            exit(1);
        }
        else if (pid == 0) {
            // This is the child process, a worker will execute from here
            char* args[] = {"worker", workerArgs, NULL};

            int ret = execv("./worker", args);

            if (ret != 0) {
                printf("Failed to execute %s: %d\n", args[0], ret);
                exit(1);
            }
        }
        else {
            // This is the parent process, it will continue to accept args
            
            // Status sent back from child process
            int status;

            while(waitpid(pid, &status, WNOHANG) == 0) {
                // Get user input again
                char newWorkerArgs[100];
                printf("%s", prompt[0]);
                fgets(newWorkerArgs, 100, stdin);
                newWorkerArgs[strcspn(newWorkerArgs, "\n")] = '\0';

                // Exit application if 'exit' is specified
                if (strcmp(newWorkerArgs, "exit") == 0) {
                    printf("Exiting...\n");
                    kill(0, SIGTERM);
                    exit(0);
                }

                // Fork another child process
                pid_t newPid = fork();

                if (newPid < 0) {
                    printf("Fork failed: %d\n", pid);
                    exit(1); 
                }
                else if (newPid == 0) {
                    char* newargs[] = {"worker", newWorkerArgs, NULL};
                    
                    int ret = execv("./worker", newargs);

                    if (ret != 0) {
                        printf("Failed to execute %s: %d\n", newargs[0], ret);
                        exit(1);
                    }
                }
                else {
                    // Set the pid from the outer loop to the pid from the new fork
                    pid = newPid;
                }
            }
    
        }
    }

    return 0;
}




/**
 * TODO:
 * 	- print information about number of available CPUs
 *  - implement option for logging results of calculations done on a particular CPU and time run
 *  
 * 
 *
 *
 *
*/