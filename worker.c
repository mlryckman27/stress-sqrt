#define _GNU_SOURCE


#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>


int main (int argc, char **argv) {

	// printf("num args: %d\n", argc);

	// int* cpuArray = (int*) malloc((argc - 1) * sizeof(int));
	// for (int i = 1; i < argc; i++)
	// 	cpuArray[i] = atoi(argv[i]);



	// Seed random number generator
	srand(time(NULL));

	// Setup CPU mask
	cpu_set_t set;
	CPU_ZERO(&set);

	// set CPU to test
	int cpu = atoi(argv[1]);
	printf("%d\n", cpu);

	CPU_SET(cpu, &set);

	// Infinite loop over square root of random number
	if (sched_setaffinity(0, sizeof(set), &set) == 0) {
		while (1) {
			sqrt(rand());
		}
	}

	return 0;
}