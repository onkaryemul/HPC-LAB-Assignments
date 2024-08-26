#include <stdio.h>
#include <omp.h>

int main(void)
{
    int num_threads;

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    // Sequential Print
    printf("\nSequential print:\n");
    for (int i = 0; i < num_threads; i++)
    {
        printf("Hello, World\n");
    }

    // Parallel Print
    omp_set_num_threads(num_threads);
    printf("\nParallel print:\n");
    #pragma omp parallel
    {
        printf("Hello, World from thread %d\n", omp_get_thread_num());
    }

    return 0;
}

