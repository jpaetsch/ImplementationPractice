#include "main.h"
#include "IO.h"


//Global variables
int thread_count;
int **A;
int **B;
int **C;  // Result matrix  A*B = C
int n; // Matrices are n x n
double timeStart, timeEnd;  // To be used for timing


// Matrix multiplication in parallel using pthreads
int main(int argc, char* argv[]) {
    //load inputs
	if(argc == 2) {
		thread_count = atoi(argv[1]);
	} else {
		printf("Invalid Input\nUsage: ./main <thread_count>\n");
		return(-1);
	}

	// Load the input that was generated using matrixgen.c (provided)
	loadinput(&A, &B, &n);

	// Allocate memory for the result
	C = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		C[i] = malloc(n * sizeof(int));
	}

	GET_TIME(timeStart);
	
	// Create threads and put each to work on multiplication of different ranks
	pthread_t multiplicationThread[thread_count];
	for(int i = 0; i < thread_count; ++i) {
		if(pthread_create(&multiplicationThread[i], NULL, thread_matrix_multiply, (void*) (intptr_t) i)) {
			// Just in case; shouldn't occur
			printf("Error with multiplication thread creation (iteration %d)\n", i);
			free_allocated_memory();
			return(-1);
		}
	}

	// Rejoin threads to confirm the work is finished - only main thread will remain
	for(int i = 0; i < thread_count; ++i) {
		if(pthread_join(multiplicationThread[i], NULL)) {
			// Just in case; shouldn't occur
			printf("Error with multiplication thread join (iteration %d)\n", i);
			free_allocated_memory();
			return(-1);
		}
	}

	GET_TIME(timeEnd);

	// Save the output after the parallel calculations
	saveoutput(C, &n, timeEnd-timeStart);

	free_allocated_memory();
	
	return 0;
}


// This function will be utilized by each of the threads for matrix multiplication
// Each thread will handle partition Pxy covering all Cij in ranges i = [i_min, i_max] and j = [j_min, j_max]
// Several assumptions are made for simpler implementation; only square (n x n) matrices are used and the number
// of threads p is a square number
void *thread_matrix_multiply(void* rank) {
	long my_rank = (long) (intptr_t) rank;
	int x, y, i_min, i_max, j_min, j_max, sqrt_p;

	// Calculate the bounds of the block Pxy for this block given the rank
	x = floor(my_rank / sqrt(thread_count));
	sqrt_p = (int)sqrt(thread_count);
	y = my_rank % sqrt_p;
	
	i_min = (n/sqrt_p)*x;
	i_max = (n/sqrt_p)*(x+1) - 1;
	j_min = (n/sqrt_p)*y;
	j_max = (n/sqrt_p)*(y+1) - 1;
	
	// i iterates through rows while j iterates through columns
	for(int i = i_min; i <= i_max; i++) {
		for(int j = j_min; j <= j_max; j++) {
			C[i][j] = 0; 
			for(int r = 0; r < n; r++){
				C[i][j] += A[i][r] * B[r][j];
			}
		}
	}
	pthread_exit(NULL);	
}


// Function to free the allocated program memory in case of pthreads creation, join issues
// or just on exit of the program
void free_allocated_memory() {
	//free malloc memory
	for(int i = 0; i < n; ++i) {
		free(A[i]);
		free(B[i]);
		free(C[i]);
	}
	free(A);
	free(B);
	free(C);
}