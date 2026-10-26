#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int matrix[3][3];
    int local_row[3];
    int search;
    int local_count = 0;
    int total_count = 0;
    int i, j;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 3)
    {
        if (rank == 0)
        {
            printf("Error: Run the program using exactly 3 processes.\n");
        }

        MPI_Finalize();
        return 0;
    }
    if (rank == 0)
    {
        printf("Enter 3 x 3 matrix:\n");
        fflush(stdout);

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("Enter element to search: ");
        fflush(stdout);
        scanf("%d", &search);
    }
    MPI_Bcast(&search, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(matrix, 3, MPI_INT,
                local_row, 3, MPI_INT,
                0, MPI_COMM_WORLD);
    for (i = 0; i < 3; i++)
    {
        if (local_row[i] == search)
        {
            local_count++;
        }
    }
    MPI_Reduce(&local_count, &total_count,
               1, MPI_INT, MPI_SUM,
               0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Number of occurrences = %d\n", total_count);
    }
    MPI_Finalize();
    return 0;
}
