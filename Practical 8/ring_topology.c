#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size, send_data, recv_data_left, recv_data_right;
    
    MPI_Init(&argc, &argv);               // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes
    
    send_data = rank; // Each process sends its rank as data
    int left = (rank - 1 + size) % size; // Left neighbor
    int right = (rank + 1) % size;       // Right neighbor

    // Exchange data with left and right neighbors
    MPI_Sendrecv(&send_data, 1, MPI_INT, right, 0, &recv_data_left, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Sendrecv(&send_data, 1, MPI_INT, left, 1, &recv_data_right, 1, MPI_INT, right, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received %d from left and %d from right\n", rank, recv_data_left, recv_data_right);

    MPI_Finalize();
    return 0;
}
