#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0)
            printf("Run with at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        printf("Enter an integer: ");
        scanf("%d", &num);
        MPI_Send(&num, 1, MPI_INT, 1, 0,
                 MPI_COMM_WORLD);
        MPI_Recv(&num, 1, MPI_INT, size - 1, 1,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Final value received by root: %d\n", num);
    }
    else {
        MPI_Recv(&num, 1, MPI_INT, rank - 1, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        num++;

        printf("Process %d sends value %d\n", rank, num);

        if (rank == size - 1) {
            MPI_Send(&num, 1, MPI_INT, 0, 1,
                     MPI_COMM_WORLD);
        }
        else {
            MPI_Send(&num, 1, MPI_INT, rank + 1, 0,
                     MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
