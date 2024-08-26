#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    int x, y;
    
    #pragma omp task shared(x)
    x = fibonacci(n - 1);

    #pragma omp task shared(y)
    y = fibonacci(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 10; // Example: Find the 10th Fibonacci number
    int result;

    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci(n);
    }

    printf("Fibonacci(%d) = %d\n", n, result);
    return 0;
}
