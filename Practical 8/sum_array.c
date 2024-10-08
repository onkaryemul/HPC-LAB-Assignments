#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, n = 10, A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int local_sum = 0, global_sum = 0;

    MPI_Init(&argc, &argv);               // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes
    
    if (size != 2) {
        if (rank == 0)
            printf("This program requires exactly 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    int half_n = n / 2; // Divide the array into two halves

    // Process P0 sums the first half, and P1 sums the second half
    if (rank == 0) {
        for (int i = 0; i < half_n; i++) {
            local_sum += A[i];
        }
        printf("Process 0 partial sum: %d\n", local_sum);
    } else if (rank == 1) {
        for (int i = half_n; i < n; i++) {
            local_sum += A[i];
        }
        printf("Process 1 partial sum: %d\n", local_sum);
    }

    // Use MPI_Reduce to combine the sums from both processes
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the final sum in process 0
    if (rank == 0) {
        printf("Total sum of the array: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
