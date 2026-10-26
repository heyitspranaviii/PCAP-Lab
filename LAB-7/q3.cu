#include <stdio.h>
#include <cuda_runtime.h>
#include <math.h>

#define N 5

__global__ void sineKernel(float *angles, float *output, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        output[i] = sinf(angles[i]);
    }
}

int main()
{
    float angles[N] = {0.0, 0.523599, 0.785398,
                       1.047198, 1.570796};
    float output[N];

    float *d_angles, *d_output;

    cudaMalloc((void **)&d_angles, N * sizeof(float));
    cudaMalloc((void **)&d_output, N * sizeof(float));

    cudaMemcpy(d_angles, angles, N * sizeof(float),
               cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (N + threads - 1) / threads;

    sineKernel<<<blocks, threads>>>(d_angles, d_output, N);

    cudaDeviceSynchronize();

    cudaMemcpy(output, d_output, N * sizeof(float),
               cudaMemcpyDeviceToHost);

    printf("Angle (radians)\tSine value\n");

    for (int i = 0; i < N; i++)
    {
        printf("%.6f\t\t%.6f\n", angles[i], output[i]);
    }

    cudaFree(d_angles);
    cudaFree(d_output);

    return 0;
}
