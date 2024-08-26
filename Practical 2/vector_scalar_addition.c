#include <stdio.h>
#include <omp.h>

int main() {
    int n = 1000000;  // Size of the vector
    int scalar = 5;   // Scalar value to add
    int vector[n];
    
    // Initialize the vector
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }
    
    // Parallel vector-scalar addition
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
    }

    // Print the first 10 elements of the result vector for verification
    for (int i = 0; i < 10; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
    return 0;
}
