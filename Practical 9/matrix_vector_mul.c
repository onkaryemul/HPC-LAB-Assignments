#include <mpi.h>
#include <stdio.h>

#define M 100  // Rows of matrix
#define N 100  // Columns of matrix

int main(int argc, char** argv) {
    int rank, size, i, j;
    int A[M][N], B[N], C[M], local_A[M], local_C[M];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Initialize matrix A and vector B
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                A[i][j] = i + j;  // Fill A with sample data
            }
        }
        for (i = 0; i < N; i++) {
            B[i] = i;  // Fill B with sample data
        }
    }

    // Start time measurement
    double start_time = MPI_Wtime();

    // Scatter rows of A to different processes
    MPI_Scatter(A, M / size * N, MPI_INT, local_A, M / size * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast vector B to all processes
    MPI_Bcast(B, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process computes its portion of matrix-vector multiplication
    for (i = 0; i < M / size; i++) {
        local_C[i] = 0;
        for (j = 0; j < N; j++) {
            local_C[i] += local_A[i * N + j] * B[j];
        }
    }

    // Gather the result from all processes
    MPI_Gather(local_C, M / size, MPI_INT, C, M / size, MPI_INT, 0, MPI_COMM_WORLD);

    // End time measurement
    double end_time = MPI_Wtime();

    if (rank == 0) {
        // Print the result
        // printf("Result Vector C:\n");
        // for (i = 0; i < M; i++) {
        //     printf("%d ", C[i]);
        // }
        // printf("\n");

        // Print time taken
        printf("Time taken for matrix-vector multiplication: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
