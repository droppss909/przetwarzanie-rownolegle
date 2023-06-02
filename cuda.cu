#include <stdio.h>
#include <curand.h>
#include <curand_kernel.h>

#define BLOCK_SIZE 256

// Kernel function to generate and print random numbers
__global__ void randomKernel(unsigned int seed, int count) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    // Initialize random number generator
    curandStateXORWOW_t state;
    curand_init(seed, tid, 0, &state);
    int g = 0;
    // Generate and print random numbers
    for (int x = 0; x < 40000; x++) {
        for (int i = tid; i < count; i += blockDim.x * gridDim.x) {
            float randNum = curand_uniform(&state);
            //printf("%d, %f\n",i*x, randNum);
        }
        
    }
}

int main() {
    int count = 1000000;
    int blockSize = BLOCK_SIZE;
    int gridSize = (count + blockSize - 1) / blockSize;

    // Generate and print random numbers on the device
    randomKernel << <gridSize, blockSize >> > (time(NULL), count);

    // Ensure all the print statements have completed
    cudaDeviceSynchronize();
    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(error));
        return -1;
    }
    return 0;
}
