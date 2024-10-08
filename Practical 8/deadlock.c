#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, data;
    
    MPI_Init(&argc, &argv);               // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes
    
    if (size != 2) {
        if (rank == 0)
            printf("This program requires exactly 2 processes to demonstrate deadlock.\n");
        MPI_Finalize();
        return 0;
    }
    
    if (rank == 0) {
        // Deadlock scenario: process 0 waits to receive, but process 1 is also waiting to receive
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Process 0 waiting to receive
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); // Process 0 sends after receiving
    } else if (rank == 1) {
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Process 1 waiting to receive
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); // Process 1 sends after receiving
    }
    
    MPI_Finalize();
    
    return 0;
}

