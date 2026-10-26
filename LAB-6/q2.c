#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int n, local_n;
    int i;
    char *s1 = NULL;
    char *s2 = NULL;
    char *result = NULL;
    char *local_s1;
    char *local_s2;
    char *local_result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        char temp1[100];
        char temp2[100];

        printf("Enter String S1: ");
        fflush(stdout);
        scanf("%s", temp1);

        printf("Enter String S2: ");
        fflush(stdout);
        scanf("%s", temp2);

        n = strlen(temp1);
        if (strlen(temp2) != n)
        {
            printf("Error: Strings must have the same length.\n");
            fflush(stdout);

            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        if (n % size != 0)
        {
            printf("Error: String length must be divisible by number of processes.\n");
            fflush(stdout);

            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        s1 = (char *)malloc(n * sizeof(char));
        s2 = (char *)malloc(n * sizeof(char));
        result = (char *)malloc(2 * n + 1);

        strcpy(s1, temp1);
        strcpy(s2, temp2);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_n = n / size;
    local_s1 = (char *)malloc(local_n * sizeof(char));
    local_s2 = (char *)malloc(local_n * sizeof(char));

    local_result = (char *)malloc(2 * local_n * sizeof(char));
    MPI_Scatter(s1, local_n, MPI_CHAR,
                local_s1, local_n, MPI_CHAR,
                0, MPI_COMM_WORLD);

    MPI_Scatter(s2, local_n, MPI_CHAR,
                local_s2, local_n, MPI_CHAR,
                0, MPI_COMM_WORLD);
    for (i = 0; i < local_n; i++)
    {
        local_result[2 * i] = local_s1[i];
        local_result[2 * i + 1] = local_s2[i];
    }
    MPI_Gather(local_result, 2 * local_n, MPI_CHAR,
               result, 2 * local_n, MPI_CHAR,
               0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        result[2 * n] = '\0';
        printf("\nString S1: %s\n", s1);
        printf("String S2: %s\n", s2);
        printf("Resultant String: %s\n", result);
        fflush(stdout);
        free(s1);
        free(s2);
        free(result);
    }

    free(local_s1);
    free(local_s2);
    free(local_result);
    MPI_Finalize();
    return 0;
}
