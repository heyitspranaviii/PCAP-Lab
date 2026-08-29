#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <omp.h>

int main()
{
    char str[100];
    int i, n;

    printf("Enter a string: ");
    scanf("%s", str);

    n = strlen(str);

    #pragma omp parallel for
    for(i = 0; i < n; i++)
    {
        int tid = omp_get_thread_num();

        if(islower(str[i]))
            str[i] = toupper(str[i]);
        else if(isupper(str[i]))
            str[i] = tolower(str[i]);

        printf("Thread %d processed index %d\n", tid, i);
    }

    printf("Toggled string = %s\n", str);

    return 0;
}
