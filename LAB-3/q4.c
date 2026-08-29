#include <stdio.h>
#include <omp.h>
#define N 10
int main() {
    int a[N] = {1,2,3,4,5,6,7,8,9,10};
    int sum;
    /* Critical */
    sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical
        sum += a[i];
    }
    printf("Critical sum = %d\n", sum);
    /* Atomic */
    sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp atomic
        sum += a[i];
    }
    printf("Atomic sum = %d\n", sum);
    /* Reduction */
    sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++)
        sum += a[i];
    printf("Reduction sum = %d\n", sum);
    /* Master */
    sum = 0;
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            #pragma omp atomic
            sum += a[i];
        }
        #pragma omp master
        printf("Master sum = %d\n", sum);
    }
    /* Locks */
    omp_lock_t lock;
    omp_init_lock(&lock);
    sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        omp_set_lock(&lock);
        sum += a[i];
        omp_unset_lock(&lock);
    }
    printf("Lock sum = %d\n", sum);
    omp_destroy_lock(&lock);
    return 0;
}
