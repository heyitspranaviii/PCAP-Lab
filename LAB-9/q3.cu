#include <stdio.h>
#include <cuda_runtime.h>
__global__ void mulRows(int *A, int *B, int *C,
                        int M, int K, int N)
{
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < M)
    {
        for (int j = 0; j < N; j++)
        {
            int sum = 0;

            for (int k = 0; k < K; k++)
                sum += A[row * K + k] * B[k * N + j];

            C[row * N + j] = sum;
        }
    }
}
__global__ void mulColumns(int *A, int *B, int *C,
                           int M, int K, int N)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (col < N)
    {
        for (int i = 0; i < M; i++)
        {
            int sum = 0;

            for (int k = 0; k < K; k++)
                sum += A[i * K + k] * B[k * N + col];

            C[i * N + col] = sum;
        }
    }
}
__global__ void mulElements(int *A, int *B, int *C,
                            int M, int K, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < M && col < N)
    {
        int sum = 0;

        for (int k = 0; k < K; k++)
            sum += A[row * K + k] * B[k * N + col];

        C[row * N + col] = sum;
    }
}

int main()
{
    int M, K, N, choice;

    printf("Enter M, K, N for A(MxK) and B(KxN): ");
    scanf("%d %d %d", &M, &K, &N);

    int sizeA = M * K;
    int sizeB = K * N;
    int sizeC = M * N;

    int *A = new int[sizeA];
    int *B = new int[sizeB];
    int *C = new int[sizeC];

    printf("Enter matrix A:\n");
    for (int i = 0; i < sizeA; i++)
        scanf("%d", &A[i]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < sizeB; i++)
        scanf("%d", &B[i]);

    printf("1. One thread per row\n");
    printf("2. One thread per column\n");
    printf("3. One thread per element\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, sizeA * sizeof(int));
    cudaMalloc(&d_B, sizeB * sizeof(int));
    cudaMalloc(&d_C, sizeC * sizeof(int));

    cudaMemcpy(d_A, A, sizeA * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeB * sizeof(int),
               cudaMemcpyHostToDevice);

    int threads = 256;

    if (choice == 1)
    {
        int blocks = (M + threads - 1) / threads;
        mulRows<<<blocks, threads>>>(d_A, d_B, d_C, M, K, N);
    }
    else if (choice == 2)
    {
        int blocks = (N + threads - 1) / threads;
        mulColumns<<<blocks, threads>>>(d_A, d_B, d_C, M, K, N);
    }
    else if (choice == 3)
    {
        dim3 threads2D(16, 16);
        dim3 blocks2D((N + 15) / 16, (M + 15) / 16);

        mulElements<<<blocks2D, threads2D>>>(
            d_A, d_B, d_C, M, K, N);
    }
    else
    {
        printf("Invalid choice\n");
        cudaFree(d_A);
        cudaFree(d_B);
        cudaFree(d_C);
        delete[] A;
        delete[] B;
        delete[] C;
        return 1;
    }

    cudaDeviceSynchronize();

    cudaMemcpy(C, d_C, sizeC * sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Result matrix C:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", C[i * N + j]);
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}

