#include <stdio.h>
#include <omp.h>
int main() {
    int A[] = {1, 2, 3, 4, 5};
    int B[] = {5, 4, 3, 2, 1};
    int C[5], D[5], E[5];
    int n = 5;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < n; i++)
                C[i] = A[i] + B[i];
        }
        #pragma omp section
        {
            for (int i = 0; i < n; i++)
                D[i] = A[i] - B[i];
        }
        #pragma omp section
        {
            for (int i = 0; i < n; i++)
                E[i] = A[i] * B[i];
        }
    }
    printf("Addition: ");
    for (int i = 0; i < n; i++)
        printf("%d ", C[i]);
    printf("\nSubtraction: ");
    for (int i = 0; i < n; i++)
        printf("%d ", D[i]);
    printf("\nMultiplication: ");
    for (int i = 0; i < n; i++)
        printf("%d ", E[i]);
    return 0;
}
