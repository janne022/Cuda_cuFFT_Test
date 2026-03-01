cmake_minimum_required(VERSION 3.18)
project(GridReaderRoot)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(core_pc)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_CUDA_STANDARD_LIBRARIES "${CMAKE_CUDA_STANDARD_LIBRARIES} -lcudart")
endif()