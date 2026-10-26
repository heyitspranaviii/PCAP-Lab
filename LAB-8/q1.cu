#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void repeatString(char *s, char *out, int len, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    if (tid < n)
    {
        for (int i = 0; i < len; i++)
            out[tid * len + i] = s[i];
    }
}

int main()
{
    char s[100], *d_s, *d_out;
    int n, len;

    printf("Enter a string: ");
    fgets(s, sizeof(s), stdin);
    printf("Enter N: ");
    scanf("%d", &n);
    if (n <= 0)
        return 0;

    len = strlen(s);

    cudaMalloc(&d_s, len);
    cudaMalloc(&d_out, len * n + 1);

    cudaMemcpy(d_s, s, len, cudaMemcpyHostToDevice);

    repeatString<<<(n + 255) / 256, 256>>>(d_s, d_out, len, n);

    char *out = (char *)malloc(len * n + 1);
    cudaMemcpy(out, d_out, len * n, cudaMemcpyDeviceToHost);
    out[len * n] = '\0';

    printf("Output String: %s\n", out);

    free(out);
    cudaFree(d_s);
    cudaFree(d_out);

    return 0;
}

