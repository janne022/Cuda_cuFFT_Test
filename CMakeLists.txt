cmake_minimum_required(VERSION 3.18)
project(CudaTest LANGUAGES CXX CUDA)

add_executable(CudaTest CudaTest.cu)

set_target_properties(CudaTest PROPERTIES 
    CXX_STANDARD 20
    CUDA_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CUDA_STANDARD_REQUIRED ON
)

find_package(CUDAToolkit REQUIRED)
target_link_libraries(CudaTest PRIVATE CUDA::cufft)

target_include_directories(CudaTest PRIVATE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})