#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    int a[100];
    int even_sum = 0, odd_sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int i;

            for(i = 0; i < n; i++)
            {
                if(a[i] % 2 == 0)
                    even_sum += a[i];
            }

            printf("Even sum calculated by Thread %d\n",
                   omp_get_thread_num());
        }

        #pragma omp section
        {
            int i;

            for(i = 0; i < n; i++)
            {
                if(a[i] % 2 != 0)
                    odd_sum += a[i];
            }

            printf("Odd sum calculated by Thread %d\n",
                   omp_get_thread_num());
        }
    }

    printf("Sum of even numbers = %d\n", even_sum);
    printf("Sum of odd numbers = %d\n", odd_sum);

    return 0;
}
