#include <stdio.h>
#include <omp.h>

int main()
{
    //First parallel region
    omp_set_num_threads(2);

    #pragma omp parallel
    {
        printf("First region: Thread %d of %d\n",
               omp_get_thread_num(),
               omp_get_num_threads());
    }

    //Second parallel region
    #pragma omp parallel num_threads(4)
    {
        printf("Second region: Thread %d of %d\n",
               omp_get_thread_num(),
               omp_get_num_threads());
    }

    return 0;
}