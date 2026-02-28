# 1. Require a modern version of CMake
cmake_minimum_required(VERSION 3.18)

# 2. THE HACK: Tell Nvidia to ignore the 2026 compiler version check
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -allow-unsupported-compiler")

# 3. Name your project and turn on CUDA!
project(CudaTest LANGUAGES CXX CUDA)

# 4. Tell CMake to build an executable using our .cu file
add_executable(CudaTest CudaTest.cu)

# 5. Force modern C++
set_property(TARGET CudaTest PROPERTY CXX_STANDARD 20)