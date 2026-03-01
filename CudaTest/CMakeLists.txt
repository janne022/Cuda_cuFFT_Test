
# CMakeList.txt : CMake project for cmake, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CudaTest "CudaTest.cu" "CudaTest.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CudaTest PROPERTY CXX_STANDARD 20)
endif()

# Add tests and install targets if needed.
find_package(CUDAToolkit REQUIRED)
target_link_libraries(CudaTest PRIVATE CUDA::cufft)

target_include_directories(CudaTest PRIVATE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})