#include <stdio.h>
#include <omp.h>
int main() {
    int a[] = {64, 25, 12, 22, 11};
    int n = 5;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        #pragma omp parallel
        {
            int local_min = min;

            #pragma omp for
            for (int j = i + 1; j < n; j++) {
                if (a[j] < a[local_min])
                    local_min = j;
            }
            #pragma omp critical
            {
                if (a[local_min] < a[min])
                    min = local_min;
            }
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}
