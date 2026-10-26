#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

#define MAX_LINES 100
#define MAX_LEN 512
int count_words(char line[])
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (isspace((unsigned char)line[i])) {
            in_word = 0;
        }
        else if (!in_word) {
            count++;
            in_word = 1;
        }
    }

    return count;
}

int main(int argc, char *argv[])
{
    int rank, size, nlines = 0;
    int words, total = 0;
    char lines[MAX_LINES][MAX_LEN];
    char line[MAX_LEN];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        FILE *fp = fopen("input.txt", "r");

        if (fp == NULL) {
            printf("Error opening input.txt\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        while (nlines < MAX_LINES &&
               fgets(lines[nlines], MAX_LEN, fp) != NULL) {
            nlines++;
        }

        fclose(fp);

        if (nlines == 0 || nlines >= size) {
            printf("Use a non-empty file with fewer lines "
                   "than the number of processes.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        for (int i = 0; i < nlines; i++) {
            MPI_Send(lines[i], strlen(lines[i]) + 1,
                     MPI_CHAR, i + 1, 0, MPI_COMM_WORLD);
        }
        for (int i = 1; i <= nlines; i++) {
            MPI_Recv(&words, 1, MPI_INT, i, 1,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("Word count from process %d: %d\n",
                   i, words);

            total += words;
        }

        printf("Total word count: %d\n", total);
    }
    else if (rank < size) {
        if (rank < size) {
            MPI_Recv(line, MAX_LEN, MPI_CHAR, 0, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            words = count_words(line);
            printf("Process %d counted %d words\n",
                   rank, words);
            MPI_Send(&words, 1, MPI_INT, 0, 1,
                     MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
