#define _GNU_SOURCE


#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>


int main (int argc, char **argv) {

	printf("num args: %d\n", argc);

	// Allocate memory for number of arguments passed to the application
	int* cpuArray = (int*) malloc((argc - 1) * sizeof(int));
	for (int i = 1; i < argc; i++)
		cpuArray[i] = atoi(argv[i]);

	/**
	 * START TEST 
	*/
	// Print out the arguments passed to the program, as a test
	for (int i = 1; i < argc; i++)
		printf("cpuArray[%d]: %d\n", i, cpuArray[i]);
	
	/**
	 * END TEST
	*/

	// Seed random number generator
	srand(time(NULL));

	// Setup CPU mask
	cpu_set_t set;
	CPU_ZERO(&set);

	// set CPU to test
	int cpu = cpuArray[1];
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


/**
 * TODO:
 * 	- fork process for each CPU specified and run sqrt on each individual process
 *  - from main process, allow user to send stop signal to each child process to stop the stress test
*/