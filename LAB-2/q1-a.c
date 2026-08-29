#include <stdio.h>
#include <omp.h>

int main()
{
    printf("Before parallel region\n");

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Thread %d is executing\n", tid);
    }

    printf("After parallel region\n");

    return 0;
}