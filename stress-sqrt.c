#define _GNU_SOURCE


#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>


int main (int argc, char **argv) {

	// Seed random number generator
	srand(time(NULL));

	// Setup CPU mask
	cpu_set_t set;
	CPU_ZERO(&set);

	// Set the CPU mask to use only CPU #0
	int cpu = 0;
	CPU_SET(cpu, &set);

	// Infinite loop over square root of random number
	if (sched_setaffinity(0, sizeof(set), &set) == 0) {
		while (1) {
			sqrt(rand());
		}
	}

	return 0;
}
