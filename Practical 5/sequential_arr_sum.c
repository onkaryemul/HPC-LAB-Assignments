#include <stdio.h>
#include <stdlib.h>
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

    // Sequential summation
    for (int i = 0; i < N; i++) {
        sum += arr[i];
    }

    printf("Sequential Total Sum: %lld\n", sum);

    free(arr);
    return 0;
}
