#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
    int rank, size;
    int error_code;
    char error_string[MPI_MAX_ERROR_STRING];
    int length;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    if (rank == 0)
    {
        printf("MPI Error Handling Demonstration\n");
        printf("Number of processes = %d\n", size);
    }
    error_code = MPI_Send(NULL, 0, MPI_INT, size + 1,
                          0, MPI_COMM_WORLD);
    if (error_code != MPI_SUCCESS)
    {
        MPI_Error_string(error_code, error_string, &length);
        printf("Process %d: MPI Error occurred:\n%s\n",
               rank, error_string);
    }
    MPI_Finalize();
    return 0;
}
