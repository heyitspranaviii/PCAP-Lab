#include <stdio.h>
#include <omp.h>

int isPrime(int n)
{
    int i;

    if(n < 2)
        return 0;

    for(i = 2; i * i <= n; i++)
    {
        if(n % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int start, end, i;

    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    #pragma omp parallel for
    for(i = start; i <= end; i++)
    {
        if(isPrime(i))
        {
            #pragma omp critical
            {
                printf("%d is prime (Thread %d)\n",
                       i, omp_get_thread_num());
            }
        }
    }

    return 0;
}