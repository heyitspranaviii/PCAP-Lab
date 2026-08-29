#include <stdio.h>
#include <omp.h>
int main()
{
    float a, b;
    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Thread %d: Addition = %.2f\n",
                   omp_get_thread_num(), a + b);
        }
        #pragma omp section
        {
            printf("Thread %d: Subtraction = %.2f\n",
                   omp_get_thread_num(), a - b);
        }
        #pragma omp section
        {
            printf("Thread %d: Multiplication = %.2f\n",
                   omp_get_thread_num(), a * b);
        }
        #pragma omp section
        {
            if(b != 0)
                printf("Thread %d: Division = %.2f\n",
                       omp_get_thread_num(), a / b);
            else
                printf("Thread %d: Division by zero not possible\n",
                       omp_get_thread_num());
        }
    }
    return 0;
}
