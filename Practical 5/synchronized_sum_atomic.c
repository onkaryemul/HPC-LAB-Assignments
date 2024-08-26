#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000  // Size of the array

void synchronized_sum_atomic(int arr[], long long *total_sum) {
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            #pragma omp atomic
            *total_sum += arr[i];
        }
    }
}

int main() {
    int *arr = (int *)malloc(N * sizeof(int));
    long long total_sum = 0;

    // Initialize the array with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Random values between 0 and 99
    }

    double start_time, end_time;

    // Measure execution time for synchronized sum using atomic
    start_time = omp_get_wtime();
    synchronized_sum_atomic(arr, &total_sum);
    end_time = omp_get_wtime();
    printf("Synchronized Total Sum (Atomic): %lld\n", total_sum);
    printf("Synchronized Execution Time (Atomic): %f seconds\n", end_time - start_time);

    free(arr);
    return 0;
}
