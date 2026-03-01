#include <iostream>
#include <vector>
#include <cufft.h>
#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

int main() {
	// Create a vector of cufftComplex with 8 elements
	thrust::host_vector<cufftComplex> radarSignal(8);

	// Fill with values representing aplitude over time
	for (size_t i = 0; i < radarSignal.size(); i++)
	{
		if (i < 4)
		{
			radarSignal[i].x = 1.0f;
			radarSignal[i].y = 0.0f;
		}
		if (i >= 4)
		{
			radarSignal[i].x = 0.0f;
			radarSignal[i].y = 0.0f;
		}
	}

	std::cout << "Filled values:\n";
	for (size_t i = 0; i < radarSignal.size(); i++)
	{
		std::cout << "Slot " << i << ": Real=" << radarSignal[i].x << ", Imag=" << radarSignal[i].y << "\n";
	}

	// Calculate bytes and allocate it
	int numBytes = radarSignal.size() * sizeof(cufftComplex);

	cufftComplex* gpuData = nullptr;

	cudaMalloc((void**)&gpuData, numBytes);

	// Copy over to gpu
	cudaMemcpy(gpuData, radarSignal.data(), numBytes, cudaMemcpyHostToDevice);

	// Handle calculation plan
	cufftHandle plan;

	cufftPlan1d(&plan, radarSignal.size(), CUFFT_C2C, 1);

	// Convert time domain to frequency domain
	cufftExecC2C(plan, gpuData, gpuData, CUFFT_FORWARD);

	// Copy back over to host
	cudaMemcpy(radarSignal.data(), gpuData, numBytes, cudaMemcpyDeviceToHost);

	// Clean up
	cufftDestroy(plan);
	cudaFree(gpuData);

	std::cout << "Frequency domain results:\n";
	for (size_t i = 0; i < radarSignal.size(); i++)
	{
		std::cout << "Slot " << i << ": Real=" << radarSignal[i].x << ", Imag=" << radarSignal[i].y << "\n";
	}

	return 0;
}