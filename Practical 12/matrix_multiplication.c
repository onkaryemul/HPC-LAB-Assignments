#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrixMultiplicationCPU(float *A, float *B, float *C, int M, int N, int P) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            float sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * P + j];
            }
            C[i * P + j] = sum;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <M> <N> <P>\n", argv[0]);
        return 1;
    }

    int M = atoi(argv[1]);  // Rows of A and C
    int N = atoi(argv[2]);  // Columns of A and Rows of B
    int P = atoi(argv[3]);  // Columns of B and C

    if (M <= 0 || N <= 0 || P <= 0) {
        fprintf(stderr, "Error: All dimensions must be positive integers.\n");
        return 1;
    }

    size_t size_A = M * N * sizeof(float);
    size_t size_B = N * P * sizeof(float);
    size_t size_C = M * P * sizeof(float);

    // Allocate memory for matrices
    float *A = (float *)malloc(size_A);
    float *B = (float *)malloc(size_B);
    float *C = (float *)malloc(size_C);

    // Initialize matrices A and B with random values
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < M * N; i++) {
        A[i] = rand() % 100;
    }
    for (int i = 0; i < N * P; i++) {
        B[i] = rand() % 100;
    }

    // Measure CPU execution time
    clock_t start = clock();
    matrixMultiplicationCPU(A, B, C, M, N, P);
    clock_t end = clock();

    double cpu_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("CPU execution time: %f seconds\n", cpu_time);

    // Free memory
    free(A);
    free(B);
    free(C);

    return 0;
}
