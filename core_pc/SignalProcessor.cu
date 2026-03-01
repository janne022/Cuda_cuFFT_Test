#include "SignalProcessor.h"

float SignalProcessor::analyzeBatch(const std::vector<int> &hostData) {
  int N = hostData.size();

  // To GPU
  thrust::device_vector<float> gpuData = hostData;
  thrust::device_vector<cufftComplex> complexVector(N);

  // Float to Complex
  thrust::transform(gpuData.begin(), gpuData.end(), complexVector.begin(),
                    FloatToComplex());

  // Create plan for cufft
  cufftHandle plan;
  cufftPlan1d(&plan, N, CUFFT_C2C, 1);

  // Run plan
  cufftExecC2C(plan, thrust::raw_pointer_cast(complexVector.data()),
               thrust::raw_pointer_cast(complexVector.data()), CUFFT_FORWARD);

  // Clean up
  cufftDestroy(plan);

  thrust::device_vector<float> magnitudes(N);

  thrust::transform(complexVector.begin(), complexVector.end(),
                    magnitudes.begin(), ComplexToMagnitude());

  auto max_iter =
      thrust::max_element(magnitudes.begin() + 1, magnitudes.begin() + N / 2);

  int peakBin = max_iter - magnitudes.begin();

  float peakMagnitude = *max_iter;

  std::cout << "Target Magnitude: " << peakMagnitude << std::endl;

  return peakMagnitude;
};