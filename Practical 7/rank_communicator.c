#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print the rank of the process and the communicator group size
    printf("Process rank: %d out of %d processes in MPI_COMM_WORLD\n", rank, size);

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
