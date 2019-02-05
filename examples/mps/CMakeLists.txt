cmake_minimum_required(VERSION 3.0)

find_package(Boost REQUIRED system program_options)
include_directories(${Boost_INCLUDE_DIRS})

find_package(VTK)
include_directories(${VTK_INCLUDE_DIRS})

include_directories(../..)

# GCC 6.0 is the latest version supported by NVCC
set(CMAKE_CUDA_HOST_COMPILER gcc-6)
# If you need to disable a warning globaly use:
# -Xcudafe \"--diag_suppress=esa_on_defaulted_function_ignored\""
# A list of valid flags can be found at:
# http://www.ssl.berkeley.edu/~jimm/grizzly_docs/SSL/opt/intel/cc/9.0/lib/locale/en_US/mcpcom.msg
# For a more local approach use:
# #pragma push
# #pragma diag_suppress = code_is_unreachable
# #pragma pop
set(CMAKE_CUDA_FLAGS ${CMAKE_CUDA_FLAGS} "--std c++14 --expt-extended-lambda -lineinfo")
add_executable(mps src/main.cu)
target_link_libraries(mps ${Boost_LIBRARIES} ${VTK_LIBRARIES})
target_compile_definitions(mps PUBLIC PARTICLE_ENABLE_CUDA BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS BOOST_FUSION_GPU_ENABLED=)
