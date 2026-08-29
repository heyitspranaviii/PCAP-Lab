#include <stdio.h>
#include <omp.h>
int main() {
    int start, end;
    long sum;
    double start_time, end_time;
    printf("Enter start and end: ");
    scanf("%d %d", &start, &end);
    /* Static */
    sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(static) reduction(+:sum)
    for (int i = start; i <= end; i++)
        sum += i;
    end_time = omp_get_wtime();
    printf("\nStatic:");
    printf("\nSum = %ld", sum);
    printf("\nTime = %lf\n", end_time - start_time);
    /* Dynamic */
    sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:sum)
    for (int i = start; i <= end; i++)
        sum += i;
    end_time = omp_get_wtime();
    printf("\nDynamic:");
    printf("\nSum = %ld", sum);
    printf("\nTime = %lf\n", end_time - start_time);
    /* Guided */
    sum = 0;
    start_time = omp_get_wtime();
    #pragma omp parallel for schedule(guided) reduction(+:sum)
    for (int i = start; i <= end; i++)
        sum += i;
    end_time = omp_get_wtime();
    printf("\nGuided:");
    printf("\nSum = %ld", sum);
    printf("\nTime = %lf\n", end_time - start_time);
    return 0;
}
