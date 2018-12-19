cmake_minimum_required(VERSION 3.0)

project(particle)

enable_language(CUDA)
enable_testing()

add_subdirectory(libs/geometry)
add_subdirectory(libs/grid)

add_subdirectory(examples/mps)
