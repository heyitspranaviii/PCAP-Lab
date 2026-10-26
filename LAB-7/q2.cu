#include <stdio.h>
#include <cuda_runtime.h>
#define N 10
#define M 3
__global__ void convolution(int *input, int *mask,
                            int *output, int n, int m)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        int sum = 0;
        int radius = m / 2;
        for (int j = 0; j < m; j++) {
            int index = i + j - radius;
            if (index >= 0 && index < n)
                sum += input[index] * mask[j];
        }
        output[i] = sum;
    }
}
int main()
{
    int input[N] = {1, 2, 3, 4, 5,
                    6, 7, 8, 9, 10};
    int mask[M] = {1, 2, 1};
    int output[N];
    int *d_input, *d_mask, *d_output;
    cudaMalloc(&d_input, N * sizeof(int));
    cudaMalloc(&d_mask, M * sizeof(int));
    cudaMalloc(&d_output, N * sizeof(int));
    cudaMemcpy(d_input, input, N * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask, mask, M * sizeof(int),
               cudaMemcpyHostToDevice);
    int threads = 256;
    int blocks = (N + threads - 1) / threads;
    convolution<<<blocks, threads>>>(
        d_input, d_mask, d_output, N, M);
    cudaMemcpy(output, d_output, N * sizeof(int),
               cudaMemcpyDeviceToHost);
    printf("Input array:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", input[i]);
    printf("\nMask array:\n");
    for (int i = 0; i < M; i++)
        printf("%d ", mask[i]);
    printf("\nConvolution output:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", output[i]);
    printf("\n");
    cudaFree(d_input);
    cudaFree(d_mask);
    cudaFree(d_output);
    return 0;
}

