#include <stdio.h>
#include <cuda_runtime.h>

__global__ void rowPower(int *A, int *B, int M, int N)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int total = M * N;
    if (idx < total)
    {
        int row = idx / N;
        int value = A[idx];
        int result = 1;
        for (int p = 0; p < row + 1; p++)
            result *= value;

        B[idx] = result;
    }
}

int main()
{
    int M, N;
    printf("Enter rows and columns: ");
    scanf("%d %d", &M, &N);
    int *A = new int[M * N];
    int *B = new int[M * N];

    printf("Enter matrix elements:\n");
    for (int i = 0; i < M * N; i++)
        scanf("%d", &A[i]);
    int *d_A, *d_B;
    cudaMalloc(&d_A, M * N * sizeof(int));
    cudaMalloc(&d_B, M * N * sizeof(int));

    cudaMemcpy(d_A, A, M * N * sizeof(int),
               cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (M * N + threads - 1) / threads;

    rowPower<<<blocks, threads>>>(d_A, d_B, M, N);
    cudaDeviceSynchronize();

    cudaMemcpy(B, d_B, M * N * sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Result matrix:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", B[i * N + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    delete[] A;
    delete[] B;

    return 0;
}

