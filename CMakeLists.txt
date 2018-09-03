cmake_minimum_required(VERSION 2.6)

project(particle)

find_package(Boost REQUIRED chrono program_options system)
include_directories(${BOOST_INCLUDE_DIRS})
include_directories(.)

find_package(Kokkos REQUIRED)
include_directories(${Kokkos_INCLUDE_DIRS})

find_package(CUDA)

#cuda_add_executable(verlet_list src/verlet_list.cpp)
#target_link_libraries(verlet_list ${Kokkos_LIBRARIES} ${Boost_LIBRARIES})

cuda_add_executable(fusion_bench src/fusion_bench.cpp)
target_compile_options(fusion_bench PUBLIC -lineinfo) # enable source code mapping in nvvp
target_link_libraries(fusion_bench ${Kokkos_LIBRARIES} ${Boost_LIBRARIES})

cuda_add_executable(coalesced_bench src/coalesced_bench.cpp)
target_compile_options(coalesced_bench PUBLIC -lineinfo) # enable source code mapping in nvvp
target_link_libraries(coalesced_bench ${Kokkos_LIBRARIES} ${Boost_LIBRARIES})

enable_testing()
add_subdirectory(libs/geometry)
