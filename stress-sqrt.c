#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char** argv) {

    int* cpuList = (int*) malloc((argc - 1) * sizeof(int));

    for (int i = 0; i < argc - 1; i++)
        cpuList[i] = atoi(argv[i + 1]);

    for (int i = 0; i < argc - 1; i++)
        printf("cpuList[%d]: %d\n", i, cpuList[i]);

    char* cpu[] = {NULL, NULL};
    scanf("%s", *cpu);
    
    while (1) {

        pid_t pid = fork();

        if (pid == 0) {
            execv("./worker", cpu);
        }

        // *cpu[0] = NULL;
        // *cpu[1] = NULL;
        scanf("%s", *cpu);
    }

    return 0;
}




/**
 * TODO:
 * 	- fork process for each CPU specified and run sqrt on each individual process
 *  - from main process, allow user to send stop signal to each child process to stop the stress test
*/