#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error: worker requires one argument\n");
        exit(1);
    }

    int cpu = atoi(argv[1]);
    //printf("Setting up worker on CPU %d", cpu);

    // Setup CPU mask
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpu, &set);

    // Seed random number generator
    srand(time(NULL));

    // Infinite loop over square root of random number
    if (sched_setaffinity(0, sizeof(set), &set) == 0) {
        while (1) {
            sqrt(rand());
        }
    }

    return 0;
}
