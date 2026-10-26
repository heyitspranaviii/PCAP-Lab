#include <stdio.h> 
#include <mpi.h> 
int main(int argc, char *argv[]) 
{ 
    int rank, size; 
    float A, B, result; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    if (size != 4) 
    { 
        if (rank == 0) 
            printf("Run using 4 processes.\n"); 
 
        MPI_Finalize(); 
        return 0; 
    } 
    if (rank == 0) 
    { 
        printf("Enter A and B: "); 
        scanf("%f %f", &A, &B); 
    } 
    MPI_Bcast(&A, 1, MPI_FLOAT, 0, MPI_COMM_WORLD); 
    MPI_Bcast(&B, 1, MPI_FLOAT, 0, MPI_COMM_WORLD); 
    if (rank == 0) 
    { 
        result = A + B; 
        printf("Addition = %.2f\n", result); 
    } 
    else if (rank == 1) 
    { 
        result = A - B; 
        printf("Subtraction = %.2f\n", result); 
    } 
    else if (rank == 2) 
    { 
        result = A * B; 
        printf("Multiplication = %.2f\n", result); 
    } 
    else if (rank == 3) 
    { 
        if (B != 0) 
        { 
            result = A / B; 
            printf("Division = %.2f\n", result); 
} 
else 
{ 
printf("Division by zero is not possible.\n"); 
} 
} 
MPI_Finalize(); 
return 0; 
}