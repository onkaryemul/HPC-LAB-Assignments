#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000  // Size of the array

void unsynchronized_sum(int arr[], long long *total_sum) {
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

    // Measure execution time for unsynchronized sum
    start_time = omp_get_wtime();
    unsynchronized_sum(arr, &total_sum);
    end_time = omp_get_wtime();
    printf("Unsynchronized Total Sum: %lld\n", total_sum);
    printf("Unsynchronized Execution Time: %f seconds\n", end_time - start_time);

    free(arr);
    return 0;
}
