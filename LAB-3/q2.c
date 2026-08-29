#include <stdio.h>
#include <omp.h>
int main() {
    int a[] = {10, 20, 30, 40, 50, 60, 70};
    int n = 7;
    int key;
    printf("Enter element to search: ");
    scanf("%d", &key);
    int found = 0;
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (a[i] == key) {
            #pragma omp critical
            {
                found = 1;
                printf("Element found at index %d by thread %d\n",
                       i, omp_get_thread_num());
            }
        }
    }
    if (!found)
        printf("Element not found\n");
    return 0;
}
