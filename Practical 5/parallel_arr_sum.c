#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000  // Size of the array

int main() {
    int *arr = (int *)malloc(N * sizeof(int));
    long long sum = 0;

    // Initialize the array with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Random values between 0 and 99
    }

    double start_time, end_time;

    // Parallel summation using OpenMP reduction
    start_time = omp_get_wtime();
    #pragma omp parallel reduction(+:sum)
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            sum += arr[i];
        }
    }
    end_time = omp_get_wtime();

    printf("Parallel Total Sum: %lld\n", sum);
    printf("Parallel Execution Time: %f seconds\n", end_time - start_time);

    free(arr);
    return 0;
}
