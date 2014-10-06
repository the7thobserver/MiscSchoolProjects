#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "helper.h"

float matrix[MATRIX_SIZE][MATRIX_SIZE];
float results[MATRIX_SIZE];
int threadsDone;
// Static
int threadStart[NUM_THREADS];
// Dynamic
int nextRow[MATRIX_SIZE];
int finishedRows = 0;

pthread_t  threads[NUM_THREADS];
pthread_mutex_t rowMutex, structMutex;

int main()
{	
	// Start timer
	clock_t start = clock(), diff;

	char* filename = "bigMatrix.txt";
	
	// Determine which version to be run here
	// runStatic(...) or runDynamic(...)
	int error = runStatic(filename);
	
	if(error == -1)
		return -1;

	// Get the speed of the program
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("\nTime taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

	pthread_exit(NULL);
	return 0;
}

