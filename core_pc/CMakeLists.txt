cmake_minimum_required(VERSION 4.2.3)

# Compiler setup
set(CUDAToolkit_ROOT "/opt/cuda")
set(CMAKE_CUDA_COMPILER "/opt/cuda/bin/nvcc")

project(GridReader LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Create the Executable
add_executable(GridReader 
    main.cpp 
    UsbLink.cpp 
    SignalProcessor.cu
)

target_include_directories(GridReader PRIVATE .)

# Add cuFFT
find_package(CUDAToolkit REQUIRED)
target_link_libraries(GridReader PRIVATE CUDA::cufft)

# Clean up CUDA flags for clangd 
if(CMAKE_CUDA_COMPILER_ID STREQUAL "NVIDIA")
    target_compile_options(GridReader PUBLIC
        $<$<COMPILE_LANGUAGE:CUDA>:--generate-code=arch=compute_75,code=sm_75>
    )
endif()

target_compile_options(GridReader PRIVATE 
    $<$<COMPILE_LANGUAGE:CUDA>:--generate-code=arch=compute_86,code=sm_86;-forward-unknown-to-host-compiler>
)