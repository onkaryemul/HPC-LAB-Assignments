#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Serial dot product calculation
float dotProductCPU(float *A, float *B, int N) {
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum += A[i] * B[i];
    }
    return sum;
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

    // Initialize vectors with random values
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // Measure time for CPU execution
    clock_t start = clock();
    float result = dotProductCPU(A, B, N);
    clock_t end = clock();

    // CPU execution time
    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU Dot Product: %f\n", result);
    printf("CPU execution time: %f seconds\n", cpu_time);

    // Free memory
    free(A);
    free(B);

    return 0;
}
