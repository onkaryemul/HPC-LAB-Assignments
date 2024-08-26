#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 100  // You can change this size for different tests

void initialize_matrices(int a[N][N], int b[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 10;  // Random values between 0 and 9
            b[i][j] = rand() % 10;  // Random values between 0 and 9
        }
    }
}

void serial_multiply(int a[N][N], int b[N][N], int result[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void parallel_multiply_static(int a[N][N], int b[N][N], int result[N][N]) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void parallel_multiply_dynamic(int a[N][N], int b[N][N], int result[N][N]) {
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void measure_time(void (*func)(int a[N][N], int b[N][N], int result[N][N]), int a[N][N], int b[N][N], int result[N][N]) {
    double start_time, end_time;
    start_time = omp_get_wtime();
    func(a, b, result);
    end_time = omp_get_wtime();
    printf("Elapsed time: %f seconds\n", end_time - start_time);
}

int main() {
    int a[N][N], b[N][N], result[N][N];

    // Seed the random number generator
    srand(time(NULL));

    // Initialize matrices
    initialize_matrices(a, b);

    printf("Serial Matrix Multiplication:\n");
    measure_time(serial_multiply, a, b, result);

    printf("\nParallel Matrix Multiplication with Static Scheduling:\n");
    measure_time(parallel_multiply_static, a, b, result);

    printf("\nParallel Matrix Multiplication with Dynamic Scheduling:\n");
    measure_time(parallel_multiply_dynamic, a, b, result);

    return 0;
}

