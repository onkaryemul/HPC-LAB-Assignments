#include <stdio.h>
#include <omp.h>

#define SIZE 200

int main() {
    int vector[SIZE];
    int scalar = 10;

    // Initialize the vector
    for (int i = 0; i < SIZE; i++) {
        vector[i] = i;
    }

    // Static scheduling with varying chunk sizes
    for (int chunk_size = 1; chunk_size <= 20; chunk_size *= 2) {
        #pragma omp parallel for schedule(static, chunk_size)
        for (int i = 0; i < SIZE; i++) {
            vector[i] += scalar;
        }
        printf("Static schedule with chunk size %d completed.\n", chunk_size);
    }

    // Dynamic scheduling with varying chunk sizes
    for (int chunk_size = 1; chunk_size <= 20; chunk_size *= 2) {
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int i = 0; i < SIZE; i++) {
            vector[i] += scalar;
        }
        printf("Dynamic schedule with chunk size %d completed.\n", chunk_size);
    }

    // Demonstration of nowait clause
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) {
            vector[i] += scalar;
        }
        printf("Nowait clause executed.\n");
    }

    return 0;
}
