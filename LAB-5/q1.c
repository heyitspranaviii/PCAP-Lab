#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    char word[100];

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
        printf("Enter a word: ");
        scanf("%s", word);
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR,
                  1, 0, MPI_COMM_WORLD);
        MPI_Recv(word, 100, MPI_CHAR, 1, 1,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Toggled word: %s\n", word);
    }
    else if (rank == 1) {
        MPI_Recv(word, 100, MPI_CHAR, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; word[i] != '\0'; i++) {
            if (islower((unsigned char)word[i]))
                word[i] = toupper((unsigned char)word[i]);
            else if (isupper((unsigned char)word[i]))
                word[i] = tolower((unsigned char)word[i]);
        }
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR,
                  0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
