#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

unsigned int my_rand(unsigned int *seed) {
    *seed = (*seed) * 1103515245 + 12345;
    return (*seed / 65536) % 32768;
}

int main() {
    long long points = 10000000;
    long long inside = 0;
    #pragma omp parallel
    {
        unsigned int seed = 1234 + omp_get_thread_num();
        #pragma omp for reduction(+:inside)
        for (long long i = 0; i < points; i++) {
            double x = (double)my_rand(&seed) / 32767.0;
            double y = (double)my_rand(&seed) / 32767.0;

            if (x * x + y * y <= 1.0)
                inside++;
        }
    }
    double pi = 4.0 * inside / points;
    printf("Points inside = %lld\n", inside);
    printf("Total points = %lld\n", points);
    printf("Calculated PI = %lf\n", pi);
    return 0;
}
