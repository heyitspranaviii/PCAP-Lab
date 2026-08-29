#include <stdio.h>
#include <omp.h>

int binaryComplement(int n)
{
    int result = 0;
    int place = 1;
    int bit;

    while(n > 0)
    {
        bit = n % 2;

        //1's complement of the bit
        bit = 1 - bit;

        result = result + bit * place;
        place = place * 10;

        n = n / 2;
    }

    return result;
}

int decimalComplement(int n)
{
    int result = 0;
    int place = 1;
    int bit;

    while(n > 0)
    {
        bit = n % 2;

        //1's complement
        bit = 1 - bit;

        result = result + bit * place;
        place = place * 2;

        n = n / 2;
    }

    return result;
}

int main()
{
    int M, N;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &M, &N);

    int A[M][N];
    int B[M][N];
    int D[M][N];

    printf("Enter matrix A:\n");

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    #pragma omp parallel for collapse(2)
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            // Border elements remain unchanged
            if(i == 0 || i == M - 1 || j == 0 || j == N - 1)
            {
                B[i][j] = A[i][j];
                D[i][j] = A[i][j];
            }
            else
            {
                B[i][j] = binaryComplement(A[i][j]);
                D[i][j] = decimalComplement(A[i][j]);
            }
        }
    }

    printf("\nMatrix B:\n");

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d\t", B[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix D:\n");

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%d\t", D[i][j]);
        }
        printf("\n");
    }

    return 0;
}
