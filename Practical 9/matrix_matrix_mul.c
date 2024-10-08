#include <mpi.h>
#include <stdio.h>

#define M 100  // Rows of matrix A
#define N 100  // Columns of matrix A, rows of matrix B
#define P 100  // Columns of matrix B

int main(int argc, char** argv) {
    int rank, size, i, j, k;
    int A[M][N], B[N][P], C[M][P], local_A[M], local_C[M];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Initialize matrix A and B
        for (i = 0; i < M; i++) {
            for (j = 0; j < N; j++) {
                A[i][j] = i + j;  // Fill A with sample data
            }
        }
        for (i = 0; i < N; i++) {
            for (j = 0; j < P; j++) {
                B[i][j] = i + j;  // Fill B with sample data
            }
        }
    }

    // Start time measurement
    double start_time = MPI_Wtime();

    // Scatter rows of A to different processes
    MPI_Scatter(A, M / size * N, MPI_INT, local_A, M / size * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast matrix B to all processes
    MPI_Bcast(B, N * P, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process computes its portion of matrix C
    for (i = 0; i < M / size; i++) {
        for (j = 0; j < P; j++) {
            local_C[i * P + j] = 0;
            for (k = 0; k < N; k++) {
                local_C[i * P + j] += local_A[i * N + k] * B[k][j];
            }
        }
    }

    // Gather the result from all processes
    MPI_Gather(local_C, M / size * P, MPI_INT, C, M / size * P, MPI_INT, 0, MPI_COMM_WORLD);

    // End time measurement
    double end_time = MPI_Wtime();

    if (rank == 0) {
        // Print the result
        // printf("Result Matrix C:\n");
        // for (i = 0; i < M; i++) {
        //     for (j = 0; j < P; j++) {
        //         printf("%d ", C[i][j]);
        //     }
        //     printf("\n");
        // }
        // Print time taken
        printf("Time taken for matrix-matrix multiplication: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
