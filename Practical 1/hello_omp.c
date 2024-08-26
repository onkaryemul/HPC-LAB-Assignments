#include <stdio.h>
#include <omp.h>

int main(void)
{
    // Set the number of threads to 4
    // omp_set_num_threads(4);

    #pragma omp parallel
    {
        printf("Hello, world. Thread number: %d\n", omp_get_thread_num());
    }

    return 0;
}