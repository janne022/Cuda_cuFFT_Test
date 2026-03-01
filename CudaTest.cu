#include <iostream>
#include <thrust/detail/raw_pointer_cast.h>
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

	// Move to GPU
	thrust::device_vector<cufftComplex> gpuData = radarSignal;

	// Handle calculation plan
	cufftHandle plan;

	cufftPlan1d(&plan, radarSignal.size(), CUFFT_C2C, 1);

	cufftComplex* gpuPtr = thrust::raw_pointer_cast(gpuData.data());

	// Convert time domain to frequency domain
	cufftExecC2C(plan, gpuPtr, gpuPtr, CUFFT_FORWARD);

	// Copy back over to host
	radarSignal = gpuData;

	// Clean up
	cufftDestroy(plan);

	std::cout << "Frequency domain results:\n";
	for (size_t i = 0; i < radarSignal.size(); i++)
	{
		std::cout << "Slot " << i << ": Real=" << radarSignal[i].x << ", Imag=" << radarSignal[i].y << "\n";
	}

	return 0;
}