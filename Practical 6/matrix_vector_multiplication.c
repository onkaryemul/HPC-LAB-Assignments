#include <stdio.h>
#include <omp.h>

#define SIZE 512  // Adjust size as needed

void matrix_vector_multiply(int A[SIZE][SIZE], int B[SIZE], int C[SIZE]) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        C[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE], C[SIZE];
    
    // Initialize matrix A and vector B with some values
    // For demonstration, initialize with 1s
    for (int i = 0; i < SIZE; i++) {
        B[i] = 1;
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 1;
        }
    }
    
    double start = omp_get_wtime();
    matrix_vector_multiply(A, B, C);
    double end = omp_get_wtime();
    
    printf("Matrix-vector multiplication completed in %f seconds\n", end - start);

    return 0;
}
