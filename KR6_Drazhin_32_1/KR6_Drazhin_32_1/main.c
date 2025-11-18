#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {
    int rank, size;
    int number;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    while (1) {
        if (rank == 0) {
            printf("-------------------------------------------------\n");
            fflush(stdout);
            scanf("%d", &number);

            if (number < 0) {
                printf("Process 0: Sending STOP signal (-1) to Process 1...\n");
            }
            else {
                printf("Process 0: Sending %d to Process 1\n", number);
            }
            fflush(stdout);

            MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

            MPI_Recv(&number, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);

            if (number < 0) {
                printf("Process 0: STOP signal returned\n");
                break;
            }

            printf("Process 0: Received %d back from Process %d\n", number, size - 1);
            fflush(stdout);
        }
        else {
            MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

            int next_rank = (rank + 1) % size;

            if (number < 0) {
                printf("Process %d: Received STOP signal. Sending to Process %d and exiting.\n", rank, next_rank);
                fflush(stdout);
                MPI_Send(&number, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
                break;
            }
            else {
                printf("Process %d: Received %d from Process %d. Sending to Process %d\n",
                    rank, number, rank - 1, next_rank);
                fflush(stdout);
                MPI_Send(&number, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
    return 0;
}