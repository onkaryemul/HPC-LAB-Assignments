#include <stdio.h>
#include <omp.h>

int main() {
    int total_sum = 0;

    #pragma omp parallel reduction(+:total_sum)
    {
        int partial_sum = 0;

        #pragma omp for
        for (int i = 1; i <= 20; i++) {
            partial_sum += i;
        }

        // Print partial sum computed by each thread
        #pragma omp critical
        {
            printf("Thread %d: Partial sum = %d\n", omp_get_thread_num(), partial_sum);
        }

        total_sum += partial_sum;
    }

    printf("Total sum: %d\n", total_sum);

    return 0;
}

