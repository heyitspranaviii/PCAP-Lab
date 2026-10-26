#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int M;
    int i;
    double *data = NULL;
    double *local_data;
    double local_sum = 0.0;
    double local_avg;
    double total_avg;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        printf("Enter M: ");
        fflush(stdout);
        scanf("%d", &M);
        data = (double *)malloc(size * M * sizeof(double));
        printf("Enter %d elements:\n", size * M);
        fflush(stdout);
        for (i = 0; i < size * M; i++)
        {
            scanf("%lf", &data[i]);
        }
    }
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    local_data = (double *)malloc(M * sizeof(double));
    MPI_Scatter(data, M, MPI_DOUBLE,
                local_data, M, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    for (i = 0; i < M; i++)
    {
        local_sum += local_data[i];
    }
    local_avg = local_sum / M;

    printf("Process %d: Average = %.2f\n", rank, local_avg);
    MPI_Reduce(&local_avg, &total_avg, 1, MPI_DOUBLE,
               MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        total_avg = total_avg / size;
        printf("Total Average = %.2f\n", total_avg);
        free(data);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}
