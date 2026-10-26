#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define THREADS 256

__global__ void vectorAdd(int *A, int *B, int *C, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
    {
        C[i] = A[i] + B[i];
    }
}

int main()
{
    int N;
    printf("Enter number of elements: ");
    scanf("%d", &N);
    if (N <= 0)
    {
        printf("N must be positive.\n");
        return 1;
    }
    int *A = (int *)malloc(N * sizeof(int));
    int *B = (int *)malloc(N * sizeof(int));
    int *C = (int *)malloc(N * sizeof(int));
    if (A == NULL || B == NULL || C == NULL)
    {
        printf("Host memory allocation failed.\n");
        free(A);
        free(B);
        free(C);
        return 1;
    }
    for (int i = 0; i < N; i++)
    {
        A[i] = i + 1;
        B[i] = i + 2;
    }
    int *d_A, *d_B, *d_C;
    cudaMalloc((void **)&d_A, N * sizeof(int));
    cudaMalloc((void **)&d_B, N * sizeof(int));
    cudaMalloc((void **)&d_C, N * sizeof(int));
    cudaMemcpy(d_A, A, N * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N * sizeof(int),
               cudaMemcpyHostToDevice);

    int blocks = (N + THREADS - 1) / THREADS;

    vectorAdd<<<blocks, THREADS>>>(d_A, d_B, d_C, N);

    cudaDeviceSynchronize();

    cudaMemcpy(C, d_C, N * sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Vector A: ");
    for (int i = 0; i < N; i++)
        printf("%d ", A[i]);

    printf("\nVector B: ");
    for (int i = 0; i < N; i++)
        printf("%d ", B[i]);

    printf("\nResult C: ");
    for (int i = 0; i < N; i++)
        printf("%d ", C[i]);

    printf("\n");
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(A);
    free(B);
    free(C);

    return 0;
}


