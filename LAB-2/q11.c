#include <stdio.h>
#include <omp.h>

int reverseNumber(int n)
{
    int rev = 0;
    int digit;

    while(n > 0)
    {
        digit = n % 10;
        rev = rev * 10 + digit;
        n = n / 10;
    }

    return rev;
}

int main()
{
    int A[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int B[9];
    int i;

    #pragma omp parallel for
    for(i = 0; i < 9; i++)
    {
        B[i] = reverseNumber(A[i]);

        printf("Thread %d reversed %d -> %d\n",
               omp_get_thread_num(),
               A[i],
               B[i]);
    }

    printf("\nOutput array:\n");

    for(i = 0; i < 9; i++)
        printf("%d ", B[i]);

    printf("\n");

    return 0;
}
