cmake_minimum_required(VERSION 2.6)

project(particle)

find_package(Boost REQUIRED chrono program_options system)
include_directories(${BOOST_INCLUDE_DIRS})
include_directories(.)

find_package(Kokkos REQUIRED)
include_directories(${Kokkos_INCLUDE_DIRS})

find_package(CUDA)

cuda_add_executable(verlet_list src/verlet_list.cpp)
target_link_libraries(verlet_list ${Kokkos_LIBRARIES} ${Boost_LIBRARIES})

enable_testing()
add_subdirectory(libs/geometry)
