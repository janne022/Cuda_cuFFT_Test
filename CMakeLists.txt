cmake_minimum_required(VERSION 3.18)

# 1. Initialize project with C++ and CUDA
project(CudaTest LANGUAGES CXX CUDA)

# 2. Create the executable
add_executable(CudaTest CudaTest.cu)

# 3. Force C++17 (Thrust needs this)
set_target_properties(CudaTest PROPERTIES
    CXX_STANDARD 20
    CUDA_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CUDA_STANDARD_REQUIRED ON
)

# 4. Link the cuFFT library
find_package(CUDAToolkit REQUIRED)
target_link_libraries(CudaTest PRIVATE CUDA::cufft)