#include <stdio.h>
#include <omp.h>

#define N 5

int main()
{
    int A[N][N], B[N][N];

    printf("Enter 5x5 matrix A:\n");

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    #pragma omp parallel for
    for(int i = 0; i < N; i++)
    {
        int max = A[i][0];
        int min = A[i][0];

        //finds maximum and minimum of this row
        for(int j = 1; j < N; j++)
        {
            if(A[i][j] > max)
                max = A[i][j];

            if(A[i][j] < min)
                min = A[i][j];
        }

        //constructs B
        for(int j = 0; j < N; j++)
        {
            if(i == j)
                B[i][j] = 0;
            else if(i > j)
                B[i][j] = max;
            else
                B[i][j] = min;
        }
    }

    printf("\nMatrix B:\n");

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d ", B[i][j]);
        }

        printf("\n");
    }

    return 0;
}
