#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Serial vector addition
void vectorAddCPU(float *A, float *B, float *C, int N) {
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <vector_size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);  // Get vector size from command line argument
    if (N <= 0) {
        fprintf(stderr, "Error: vector size must be a positive integer.\n");
        return 1;
    }

    size_t size = N * sizeof(float);

    // Allocate memory for vectors
    float *A = (float *)malloc(size);
    float *B = (float *)malloc(size);
    float *C = (float *)malloc(size);
    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return 1;
    }

    // Initialize vectors with random values
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // Measure time for CPU execution
    clock_t start = clock();
    vectorAddCPU(A, B, C, N);
    clock_t end = clock();

    // CPU execution time
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU execution time: %f seconds\n", cpu_time);

    // Free memory
    free(A);
    free(B);
    free(C);

    return 0;
}

// N = 10^5, 10^6, 10^7)
