#include <stdio.h>
#include <omp.h>
#include <limits.h>

#define N 1000  // Size of the vectors

int main() {
    int a[N], b[N];
    long long min_product = LLONG_MAX;

    // Initialize vectors a and b
    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
        b[i] = N - i;
    }

    // Parallel reduction to find the minimum scalar product
    #pragma omp parallel for reduction(min: min_product)
    for (int i = 0; i < N; i++) {
        long long product = a[i] * b[i];
        if (product < min_product) {
            min_product = product;
        }
    }

    printf("Minimum Scalar Product: %lld\n", min_product);
    return 0;
}

