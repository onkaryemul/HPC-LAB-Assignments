#include <stdio.h>
#include <omp.h>

#define SIZE 512  // Adjust size as needed

void matrix_multiply(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    
    // Initialize matrices A and B with some values
    // For demonstration, initialize with 1s
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
    
    double start = omp_get_wtime();
    matrix_multiply(A, B, C);
    double end = omp_get_wtime();
    
    printf("Matrix multiplication completed in %f seconds\n", end - start);

    return 0;
}
