#ifndef CS141Lab1_h
#define CS141Lab1_h

#include <pthread.h>

#define MATRIX_SIZE 1000
#define NUM_THREADS 4
#define K 25

extern float matrix[MATRIX_SIZE][MATRIX_SIZE];
extern float results[MATRIX_SIZE];
extern int threadsDone;
extern pthread_t threads[NUM_THREADS];
extern pthread_mutex_t rowMutex, structMutex;

// Static division - holds all the start points
extern int threadStart[NUM_THREADS];
// Dynamic
extern int nextRow[MATRIX_SIZE];
extern int finishedRows; 

// Hold the norm for a dynamic run
struct data
{
	float temp;
};

void printMatrix();
void printResults();
int findNorm();
void* calculateNormStatic(void* start);
int spawnThreadsStatic();
int parseFile(char* filename);
int runStatic(char* filename);
int runDynamic(char* filename);
int getNextRow();


#endif
