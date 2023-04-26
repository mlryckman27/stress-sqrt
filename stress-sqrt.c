#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


char* cpu[] = {NULL, NULL};


int main(int argc, char** argv) {

    int status;

    pid_t pid;
    char cpu[3];

    while (1) {
        fgets(cpu, 3, stdin);
        int cpuArg = atoi(cpu);

        pid = fork();
        if (pid < 0) {
            printf("Fork failed: %d\n", pid);
            exit(1);
        }
        else if (pid == 0) {
            char** args;
            args[0] = (char*) malloc(8 * sizeof(char));
            args[1] = (char*) malloc(3 * sizeof(char));

            args[0] = "./worker";
            args[1] = cpu;
            printf("%s\n", args[0]);
            printf("%s\n", args[1]);
            //execv(args[0], args);
            //printf("CPU to test: %d\n", cpuArg);
        }
        else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}




/**
 * TODO:
 * 	- fork process for each CPU specified and run sqrt on each individual process
 *  - from main process, allow user to send stop signal to each child process to stop the stress test
*/