#include<stdio.h>
#include <stdlib.h>
#include "helper.h"

// Prints the stored matrix to the console
void printMatrix()
{
	printf("\nMatrix\n");
	int i, j;

	for(i = 0; i < MATRIX_SIZE; i++)
	{
		for(j = 0; j < MATRIX_SIZE; j++)
			printf("%f ",matrix[i][j]);
		printf("\n");
	}
}

// Prints the results matrix of the static run to the console
void printResults()
{
	printf("\nResults\n");

	int i;
	for(i = 0; i < MATRIX_SIZE; i++)
	{
		printf("%f ", results[i]);
	}
	printf("\n");
}

// Find the norm from the results matrix - static run
int findNorm()
{
	int i;
	float max = 0;
	for(i = 0; i < MATRIX_SIZE; i++)
	{
		if(results[i] > max)
			max = results[i];
	}

	printf("Norm is %f\n", max);
}

// Calculate the norm statically
void* calculateNormStatic(void* start)
{
	int* index = (int*) start;
	int i, j;
	float result = 0;
	int stop = *index + (MATRIX_SIZE / NUM_THREADS);
	
	// Sum over the different rows
	for(j = *index; j < stop; j++)
	{
		// Go accross the rows
		for(i = 0; i < MATRIX_SIZE; i++)
		{
			result += matrix[j][i];
		}
	
		results[j] = result;
		result = 0;
	}

	// Say thread is finished
	threadsDone++;

	// Kill the thread
	pthread_exit(NULL);
}

// Calculate the norm dynamically
void* calculateNormDynamic(void* temp)
{
	struct data* dPack = (struct data*) temp;
	
	// Get the next row, lock it with a mutex to ensure nothing is skipped or double counted
	pthread_mutex_lock(&rowMutex);
	int index = getNextRow();
	pthread_mutex_unlock(&rowMutex);

	float norm = 0;
	int i;
	int j = 0;
	float result = 0;

	// While there is still norms to be calculated from the matrix
	while(index < MATRIX_SIZE)
	{
		// Interim norm update - updated after each new index + consecutive rows assignment is obtained
		norm = dPack -> temp;

		// While there are still consecutive rows to be worked on
		while(j < K)
		{
			// Find the norm
			for(i = 0; i < MATRIX_SIZE; i++)
			{
				result += matrix[index][i];
			}

			// Recalculate the norm - if it's bigger than the saved norm replace it
			if(norm < result)
				norm = result;

			// Reset:
			//		result   temporary holder for the current rows norm
			//		j		 counter for the index
			//		index    the row that will be worked on
			result = 0;
			j++;
			index++;
		}

		// Save data - lock so the threads don't step on each other
		pthread_mutex_lock(&structMutex);
		float x = dPack -> temp;
		if(x < norm)
			dPack -> temp = norm;
		pthread_mutex_unlock(&structMutex);

		// Go see if there's more work to be done
		j = 0;
		pthread_mutex_lock(&rowMutex);
		index = getNextRow();
		pthread_mutex_unlock(&rowMutex);
	}

	// Say thread is finished
	threadsDone++;

	// Kill the thread
	pthread_exit(NULL);
}

// Parses doubles from an input file
int parseFile(char* filename)
{
	char input;
	FILE *file;
	
	int row = 0; 
	int column = 0;

	// Open file in read mode
	file = fopen(filename,"r"); 
 
	// Check to see if the file has contents
	if(file == NULL)
	{
		printf("ERROR: Can't open file.\n");
		return -1;
	}

	float d;
	int i, j;

	// Read the file float by float and store it into the matrix
	for(i = 0; i < MATRIX_SIZE; i++)
	{
		for(j = 0; j < MATRIX_SIZE; j++)
		{
			fscanf (file, "%f", &d);

			if(d < 0)
				d = -d;

			matrix[i][j] = d;
		}
	}

	fclose(file);

	return 0;
}

// Statically divide the computation between threads
int spawnThreadsStatic()
{	
	int i;
	int rc;

	for(i = 0; i < NUM_THREADS; i++)
	{
		threadStart[i] = i * MATRIX_SIZE / NUM_THREADS;
	
		rc = pthread_create(&threads[i], NULL, calculateNormStatic, (void *) &threadStart[i]);

		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			return -1;
		}
	}
}

// Run the program statically
int runStatic(char* filename)
{
	int error = parseFile(filename);	

	if(error == -1)
	{
		printf("Couldn't open the file\n");
		return -1;
	}
	
	error = spawnThreadsStatic();

	if(error == -1)
	{
		printf("Error spawning threads.");
		return -1;
	}

	// Wait for all threads to finish work on the matrix
	while(threadsDone != NUM_THREADS)
	{
		// Waiting
	}

	findNorm();

	return 0;
}

// Run the program dynamically
int runDynamic(char* filename)
{
	int error = parseFile(filename);	

	if(error == -1)
	{
		printf("Couldn't open the file\n");
		return -1;
	}
	
	struct data* result = malloc(sizeof(struct data));
	result -> temp = 0;
	
	int rc;
	long i;

	for(i = 0; i < NUM_THREADS; i++)
	{
		rc = pthread_create(&threads[i], NULL, calculateNormDynamic, (void *) result);

		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			error = -1;
		}
	}

	if(error == -1)
	{
		printf("Error spawning threads.");
		return -1;
	}

	// Wait for all threads to finish work on the matrix
	while(threadsDone != NUM_THREADS)
	{
		// Waiting
	}

	float x = result-> temp;
	printf("result: %f\n", x);

	return 0;
}

// Get the next row  for the threads to work on
int getNextRow()
{
	int nextRow = finishedRows;
	finishedRows += K;
	
	return nextRow;
}