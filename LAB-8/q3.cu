#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void countWord(char *words, char *target,
                          int *count, int n, int maxLen)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    if (tid < n)
    {
        int i = 0;
        int match = 1;

        while (words[tid * maxLen + i] != '\0' ||
               target[i] != '\0')
        {
            if (words[tid * maxLen + i] != target[i])
            {
                match = 0;
                break;
            }
            i++;
        }

        if (match)
            atomicAdd(count, 1);
    }
}

int main()
{
    char sentence[500], target[100];
    char words[100][100];
    char *d_words, *d_target;
    int *d_count;
    int n = 0;

    printf("Enter sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("Enter word to search: ");
    scanf("%99s", target);

    char *token = strtok(sentence, " \t");
    while (token != NULL && n < 100)
    {
        snprintf(words[n], sizeof(words[n]), "%s", token);
        n++;
        token = strtok(NULL, " \t");
    }

    if (n == 0)
    {
        printf("Occurrences: 0\n");
        return 0;
    }

    cudaMalloc(&d_words, sizeof(words));
    cudaMalloc(&d_target, sizeof(target));
    cudaMalloc(&d_count, sizeof(int));

    cudaMemcpy(d_words, words, sizeof(words),
               cudaMemcpyHostToDevice);
    cudaMemcpy(d_target, target, sizeof(target),
               cudaMemcpyHostToDevice);

    cudaMemset(d_count, 0, sizeof(int));

    countWord<<<(n + 255) / 256, 256>>>(
        d_words, d_target, d_count, n, 100);

    int count;
    cudaMemcpy(&count, d_count, sizeof(int),
               cudaMemcpyDeviceToHost);

    printf("Occurrences of '%s': %d\n", target, count);

    cudaFree(d_words);
    cudaFree(d_target);
    cudaFree(d_count);

    return 0;
}

