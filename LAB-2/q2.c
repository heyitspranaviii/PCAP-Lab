#include <stdio.h>
#include <omp.h>

int main()
{
    int i;

    printf("Enter integer value: ");
    scanf("%d", &i);

    #pragma omp parallel
    {
        int x = omp_get_thread_num();

        printf("Thread %d: (%d, %d)\n", x, i, x);
    }

    return 0;
}
