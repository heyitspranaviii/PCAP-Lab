#include <stdio.h>
#include <cuda_runtime.h>

__global__ void transformMatrix(int *A, int *B, int M, int N)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < M * N)
    {
        int i = idx / N;
        int j = idx % N;
        if (i == 0 || i == M - 1 ||
            j == 0 || j == N - 1)
        {
            B[idx] = A[idx];
        }
        else
        {
            switch (A[idx])
            {
                case 5:  B[idx] = 10;  break;
                case 8:  B[idx] = 111; break;
                case 4:  B[idx] = 11;  break;
                case 10: B[idx] = 101; break;
                default: B[idx] = ~A[idx]; break;
            }
        }
    }
}

int main()
{
    int M, N;

    printf("Enter rows and columns: ");
    scanf("%d %d", &M, &N);

    int size = M * N;

    int *A = new int[size];
    int *B = new int[size];

    printf("Enter matrix A:\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &A[i]);

    int *d_A, *d_B;

    cudaMalloc(&d_A, size * sizeof(int));
    cudaMalloc(&d_B, size * sizeof(int));

    cudaMemcpy(d_A, A, size * sizeof(int),
               cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (size + threads - 1) / threads;

    transformMatrix<<<blocks, threads>>>(d_A, d_B, M, N);
    cudaDeviceSynchronize();

    cudaMemcpy(B, d_B, size * sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Output matrix B:\n");
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


