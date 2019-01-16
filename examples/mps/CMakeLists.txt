cmake_minimum_required(VERSION 3.0)

find_package(Boost REQUIRED system program_options)
include_directories(${Boost_INCLUDE_DIRS})

find_package(VTK)
include_directories(${VTK_INCLUDE_DIRS})

include_directories(../..)

# GCC 6.0 is the latest version supported by NVCC
set(CMAKE_CUDA_HOST_COMPILER gcc-6)
set(CMAKE_CUDA_FLAGS ${CMAKE_CUDA_FLAGS} "--expt-extended-lambda -lineinfo")
add_executable(mps src/main.cu)
target_link_libraries(mps ${Boost_LIBRARIES} ${VTK_LIBRARIES})
target_compile_definitions(mps PUBLIC PARTICLE_ENABLE_CUDA)
