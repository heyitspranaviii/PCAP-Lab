#include <stdio.h>
#include <cuda_runtime.h>
#define N 10
__global__ void vectorAdd(int *A, int *B, int *C)
{
    int i = threadIdx.x;
    C[i] = A[i] + B[i];
}
int main()
{
    int A[N], B[N], C[N];
    int *d_A, *d_B, *d_C;
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;
        B[i] = i + 10;
    }
    cudaMalloc(&d_A, N * sizeof(int));
    cudaMalloc(&d_B, N * sizeof(int));
    cudaMalloc(&d_C, N * sizeof(int));
    cudaMemcpy(d_A, A, N * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, N * sizeof(int),
               cudaMemcpyHostToDevice);
    vectorAdd<<<1, N>>>(d_A, d_B, d_C);
    cudaMemcpy(C, d_C, N * sizeof(int),
               cudaMemcpyDeviceToHost);
    printf("Vector Addition:\n");
    for (int i = 0; i < N; i++)
        printf("%d + %d = %d\n", A[i], B[i], C[i]);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    return 0;
}
