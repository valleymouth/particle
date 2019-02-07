cmake_minimum_required(VERSION 3.0)

# Particle include path 
include_directories(../../)

find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(left_test test/left.cpp)
target_link_libraries(left_test ${Boost_LIBRARIES})
add_test(NAME left_test COMMAND left_test)

add_executable(right_test test/right.cpp)
target_link_libraries(right_test ${Boost_LIBRARIES})
add_test(NAME right_test COMMAND right_test)

find_package(CUDA)
if(CUDA_FOUND)
  # GCC 6.0 is the latest version supported by NVCC
  set(CUDA_HOST_COMPILER gcc-6)
  set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} -Wno-deprecated-declarations)

  file(COPY test/left.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/left.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/left.cu)
  cuda_add_executable(left_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/left.cu)
  target_link_libraries(left_test_cuda ${Boost_LIBRARIES})
  add_test(NAME left_test_cuda COMMAND left_test_cuda)

  file(COPY test/right.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/right.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/right.cu)
  cuda_add_executable(right_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/right.cu)
  target_link_libraries(right_test_cuda ${Boost_LIBRARIES})
  add_test(NAME right_test_cuda COMMAND right_test_cuda)
endif()
