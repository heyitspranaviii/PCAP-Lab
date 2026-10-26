#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, i;
    long long fact = 1;
    long long prefix_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    i = rank + 1;
    for (int j = 1; j <= i; j++)
        fact *= j;

    MPI_Scan(&fact, &prefix_sum, 1, MPI_LONG_LONG,
             MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d: %d! = %lld, Prefix Sum = %lld\n",
           rank, i, fact, prefix_sum);

    if (rank == size - 1)
        printf("Final Sum = %lld\n", prefix_sum);

    MPI_Finalize();
    return 0;
}
