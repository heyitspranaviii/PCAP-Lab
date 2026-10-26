#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int matrix[4][4];
    int local_row[4];
    int result[4][4];
    int prefix[4];
    int i, j;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 4)
    {
        if (rank == 0)
        {
            printf("Run the program using exactly 4 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }
    if (rank == 0)
    {
        printf("Enter 4 x 4 matrix:\n");
        fflush(stdout);

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }
    }
    MPI_Scatter(matrix, 4, MPI_INT,
                local_row, 4, MPI_INT,
                0, MPI_COMM_WORLD);
    MPI_Scan(local_row, prefix, 4,
             MPI_INT, MPI_SUM,
             MPI_COMM_WORLD);
    MPI_Gather(prefix, 4, MPI_INT,
               result, 4, MPI_INT,
               0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Output matrix:\n");

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                printf("%d ", result[i][j]);
            }

            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
