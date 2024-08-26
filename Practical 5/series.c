#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 1; i <= 10; i++) {
                printf("Thread %d: Series of 2: %d\n", omp_get_thread_num(), 2 * i);
            }
        }

        #pragma omp section
        {
            for (int i = 1; i <= 10; i++) {
                printf("Thread %d: Series of 4: %d\n", omp_get_thread_num(), 4 * i);
            }
        }
    }

    return 0;
}
