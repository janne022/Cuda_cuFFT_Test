cmake_minimum_required(VERSION 3.18)

set(CUDAToolkit_ROOT "/opt/cuda")
set(CMAKE_CUDA_COMPILER "/opt/cuda/bin/nvcc")

project(CudaTest LANGUAGES CXX CUDA)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(CudaTest CudaTest.cu)

set_target_properties(CudaTest PROPERTIES
    CXX_STANDARD 20
    CUDA_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CUDA_STANDARD_REQUIRED ON
)

find_package(CUDAToolkit REQUIRED)
target_link_libraries(CudaTest PRIVATE CUDA::cufft)