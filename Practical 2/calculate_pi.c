#include <stdio.h>
#include <omp.h>

int main() {
    long num_steps = 1000000000;
    double step = 1.0 / (double)num_steps;
    double sum = 0.0;
    
    // Parallel calculation of Pi
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction(+:sum)
        for (int i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    }
    
    double pi = step * sum;
    printf("Calculated value of Pi: %.15f\n", pi);
    
    return 0;
}
