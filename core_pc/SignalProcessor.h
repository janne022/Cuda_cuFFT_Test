#pragma once

#include <iostream>
#include <thrust/detail/raw_pointer_cast.h>
#include <cufft.h>
#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/extrema.h>

// Translate float to complex
struct FloatToComplex {
    __host__ __device__
    cufftComplex operator()(const float& x) const{
        cufftComplex c;
        c.x = x;
        c.y = 0.0f;

        return c;
    }
};

// Used to find the length of the complex vector
struct ComplexToMagnitude {
    __host__ __device__
    float operator()(const cufftComplex& c) const{
        return sqrtf(c.x * c.x + c.y * c.y);
    }
};

struct PeakData{
    float magnitude;
    float frequency;
};

class SignalProcessor{
    public:
    PeakData analyzeBatch(const std::vector<int>& hostData);
};