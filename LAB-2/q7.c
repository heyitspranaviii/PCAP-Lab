#include <stdio.h>
#include <omp.h>

long long fibonacci(int n)
{
    if(n <= 1)
        return n;

    long long a = 0, b = 1, c;
    int i;

    for(i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

int main()
{
    int A[] = {10, 13, 5, 6};
    int B[4];
    int i;

    #pragma omp parallel for
    for(i = 0; i < 4; i++)
    {
        B[i] = fibonacci(A[i]);

        printf("Thread %d calculated Fibonacci(%d) = %d\n",
               omp_get_thread_num(), A[i], B[i]);
    }

    printf("\nOutput:\n");

    for(i = 0; i < 4; i++)
        printf("%d ", B[i]);

    printf("\n");

    return 0;
}
