#include <stdio.h>
#include <omp.h>

int main() {
    const char* family_members[] = {"Onkar", "Yogesh", "Anand", "Nagmani"};
    int n = 4;

    #pragma omp parallel num_threads(n)
    {
        int id = omp_get_thread_num();
        printf("Thread %d: %s\n", id, family_members[id]);
    }

    return 0;
}
