#include <stdio.h>
#include <omp.h>

int main() {
    int total_sum = 0;
    int partial_sum = 0;

    #pragma omp parallel 
    {
        #pragma omp for lastprivate(partial_sum)
        for (int i = 1; i <= 20; i++) {
            partial_sum += i;
        }

        #pragma omp critical
        total_sum += partial_sum;
    }

    printf("Total sum: %d\n", total_sum);

    return 0;
}
