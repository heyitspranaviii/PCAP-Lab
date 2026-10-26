#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void reverseWords(char *s, int *start,
                             int *end, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    if (tid < n)
    {
        int l = start[tid];
        int r = end[tid];

        while (l < r)
        {
            char temp = s[l];
            s[l] = s[r];
            s[r] = temp;
            l++;
            r--;
        }
    }
}

int main()
{
    char s[500];
    int start[100], end[100], n = 0;
    char *d_s;
    int *d_start, *d_end;

    printf("Enter a sentence: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    int len = strlen(s);
    int i = 0;

    while (i < len)
    {
        if (s[i] == ' ')
        {
            i++;
            continue;
        }

        start[n] = i;

        while (i < len && s[i] != ' ')
            i++;

        end[n] = i - 1;
        n++;
    }

    if (n == 0)
    {
        printf("Output: %s\n", s);
        return 0;
    }

    cudaMalloc(&d_s, len + 1);
    cudaMalloc(&d_start, n * sizeof(int));
    cudaMalloc(&d_end, n * sizeof(int));

    cudaMemcpy(d_s, s, len + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_start, start, n * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_end, end, n * sizeof(int),
               cudaMemcpyHostToDevice);

    reverseWords<<<(n + 255) / 256, 256>>>(
        d_s, d_start, d_end, n);

    cudaMemcpy(s, d_s, len + 1, cudaMemcpyDeviceToHost);

    printf("Reversed words: %s\n", s);

    cudaFree(d_s);
    cudaFree(d_start);
    cudaFree(d_end);

    return 0;
}


