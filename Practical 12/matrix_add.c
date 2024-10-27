#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Serial matrix addition using 2D arrays
void matrixAddCPU(float **A, float **B, float **C, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to allocate a 2D array
float** allocate2DArray(int M, int N) {
    float **array = (float **)malloc(M * sizeof(float *));
    for (int i = 0; i < M; i++) {
        array[i] = (float *)malloc(N * sizeof(float));
    }
    return array;
}

// Function to free a 2D array
void free2DArray(float **array, int M) {
    for (int i = 0; i < M; i++) {
        free(array[i]);
    }
    free(array);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <rows> <columns>\n", argv[0]);
        return 1;
    }

    int M = atoi(argv[1]);  // Get number of rows from command line argument
    int N = atoi(argv[2]);  // Get number of columns from command line argument
    if (M <= 0 || N <= 0) {
        fprintf(stderr, "Error: both dimensions must be positive integers.\n");
        return 1;
    }

    // Allocate memory for matrices
    float **A = allocate2DArray(M, N);
    float **B = allocate2DArray(M, N);
    float **C = allocate2DArray(M, N);

    // Initialize matrices with random values
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }

    // Measure time for CPU execution
    clock_t start = clock();
    matrixAddCPU(A, B, C, M, N);
    clock_t end = clock();

    // CPU execution time
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU execution time: %f seconds\n", cpu_time);

    // Free memory
    free2DArray(A, M);
    free2DArray(B, M);
    free2DArray(C, M);

    return 0;
}
