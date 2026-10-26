#include <stdio.h>
#include <cuda_runtime.h>
__global__ void addRows(int *A, int *B, int *C,
                        int M, int N)
{
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < M)
    {
        for (int j = 0; j < N; j++)
        {
            int idx = row * N + j;
            C[idx] = A[idx] + B[idx];
        }
    }
}
__global__ void addColumns(int *A, int *B, int *C,
                           int M, int N)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (col < N)
    {
        for (int i = 0; i < M; i++)
        {
            int idx = i * N + col;
            C[idx] = A[idx] + B[idx];
        }
    }
}
__global__ void addElements(int *A, int *B, int *C,
                            int M, int N)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < M * N)
        C[idx] = A[idx] + B[idx];
}

int main()
{
    int M, N, choice;
    printf("Enter rows and columns: ");
    scanf("%d %d", &M, &N);
    int size = M * N;
    int *A = new int[size];
    int *B = new int[size];
    int *C = new int[size];

    printf("Enter matrix A:\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &A[i]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &B[i]);

    printf("1. One thread per row\n");
    printf("2. One thread per column\n");
    printf("3. One thread per element\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, size * sizeof(int));
    cudaMalloc(&d_B, size * sizeof(int));
    cudaMalloc(&d_C, size * sizeof(int));

    cudaMemcpy(d_A, A, size * sizeof(int),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size * sizeof(int),
               cudaMemcpyHostToDevice);

    int threads = 256;

    if (choice == 1)
    {
        int blocks = (M + threads - 1) / threads;
        addRows<<<blocks, threads>>>(d_A, d_B, d_C, M, N);
    }
    else if (choice == 2)
    {
        int blocks = (N + threads - 1) / threads;
        addColumns<<<blocks, threads>>>(d_A, d_B, d_C, M, N);
    }
    else if (choice == 3)
    {
        int blocks = (size + threads - 1) / threads;
        addElements<<<blocks, threads>>>(d_A, d_B, d_C, M, N);
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

    cudaMemcpy(C, d_C, size * sizeof(int),
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

