#include <stdio.h>
#include <omp.h>

int main()
{
    int A[100][100], X[100], B[100];
    int m, n, i, j;

    printf("Enter rows and columns: ");
    scanf("%d %d", &m, &n);

    printf("Enter matrix A:\n");
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter vector X:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &X[i]);

    #pragma omp parallel for
    for(i = 0; i < m; i++)
    {
        B[i] = 0;

        for(j = 0; j < n; j++)
            B[i] += A[i][j] * X[j];
    }

    printf("Result vector:\n");

    for(i = 0; i < m; i++)
        printf("%d ", B[i]);

    printf("\n");

    return 0;
}