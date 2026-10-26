#include <stdio.h> 
#include <ctype.h> 
#include <mpi.h> 
int main(int argc, char *argv[]) 
{ 
int rank, size; 
char str[100]; 
char ch; 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
if (rank == 0) 
{ 
} 
printf("Enter string: "); 
scanf("%s", str); 
MPI_Bcast(str, 100, MPI_CHAR, 0, MPI_COMM_WORLD); 
if (rank < size) 
{ 
} 
ch = str[rank]; 
if (islower(ch)) 
ch = toupper(ch); 
else if (isupper(ch)) 
ch = tolower(ch); 
printf("Process %d: %c -> %c\n", rank, str[rank], ch); 
MPI_Finalize(); 
return 0; 
}