#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void reverseString(char *s, int len)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    if (tid < len / 2)
    {
        int j = len - 1 - tid;

        char temp = s[tid];
        s[tid] = s[j];
        s[j] = temp;
    }
}

int main()
{
    char s[500];
    char *d_s;

    printf("Enter a string: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    int len = strlen(s);

    if (len == 0)
    {
        printf("Reversed string: %s\n", s);
        return 0;
    }

    cudaMalloc(&d_s, len + 1);
    cudaMemcpy(d_s, s, len + 1, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (len / 2 + threads - 1) / threads;

    if (blocks > 0)
        reverseString<<<blocks, threads>>>(d_s, len);

    cudaMemcpy(s, d_s, len + 1, cudaMemcpyDeviceToHost);

    printf("Reversed string: %s\n", s);

    cudaFree(d_s);

    return 0;
}

