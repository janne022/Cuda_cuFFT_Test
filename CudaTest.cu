#include <iostream>
#include <vector>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// 1. THE KERNEL (Runs on the GPU)
__global__ void MultiplyOnGPU(int* deviceArray) {
    int myThreadID = threadIdx.x; 
    deviceArray[myThreadID] = deviceArray[myThreadID] * 10;
}

int main() {
    const int arraySize = 5;
    const int bytesToAllocate = arraySize * sizeof(int); 

    // A. Create Host (CPU) Data
    std::vector<int> cpuData = { 1, 2, 3, 4, 5 };
    int* gpuData = nullptr;

    // B. Allocate Device (GPU) Memory
    cudaMalloc((void**)&gpuData, bytesToAllocate);

    // C. Copy CPU -> GPU
    cudaMemcpy(gpuData, cpuData.data(), bytesToAllocate, cudaMemcpyHostToDevice);
    std::cout << "Data sent to GPU...\n";

    // D. Launch Kernel: 1 Block, 5 Threads
    MultiplyOnGPU<<<1, arraySize>>>(gpuData);
    cudaDeviceSynchronize(); 
    std::cout << "GPU finished crunching numbers!\n";

    // E. Copy GPU -> CPU
    cudaMemcpy(cpuData.data(), gpuData, bytesToAllocate, cudaMemcpyDeviceToHost);

    // F. Clean up GPU Memory
    cudaFree(gpuData);

    // G. Print Results
    std::cout << "--- Final Results ---\n";
    for (int i = 0; i < arraySize; i++) {
        std::cout << "Slot " << i << ": " << cpuData[i] << "\n";
    }

    return 0;
}