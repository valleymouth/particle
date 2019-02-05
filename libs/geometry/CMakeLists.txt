cmake_minimum_required(VERSION 3.0)

# Particle include path 
include_directories(../../)

find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(add_test test/add.cpp)
target_link_libraries(add_test ${Boost_LIBRARIES})
add_test(NAME add_test COMMAND add_test)

add_executable(add_operator_test test/add_operator.cpp)
target_link_libraries(add_operator_test ${Boost_LIBRARIES})
add_test(NAME add_operator_test COMMAND add_operator_test)

add_executable(as_test test/as.cpp)
target_link_libraries(as_test ${Boost_LIBRARIES})
add_test(NAME as_test COMMAND as_test)

add_executable(cast_test test/cast.cpp)
target_link_libraries(cast_test ${Boost_LIBRARIES})
add_test(NAME cast_test COMMAND cast_test)

add_executable(contains_test test/contains.cpp)
target_link_libraries(contains_test ${Boost_LIBRARIES})
add_test(NAME contains_test COMMAND contains_test)

add_executable(distance_test test/distance.cpp)
target_link_libraries(distance_test ${Boost_LIBRARIES})
add_test(NAME distance_test COMMAND distance_test)

add_executable(div_test test/div.cpp)
target_link_libraries(div_test ${Boost_LIBRARIES})
add_test(NAME div_test COMMAND div_test)

add_executable(div_operator_test test/div_operator.cpp)
target_link_libraries(div_operator_test ${Boost_LIBRARIES})
add_test(NAME div_operator_test COMMAND div_operator_test)

add_executable(dot_test test/dot.cpp)
target_link_libraries(dot_test ${Boost_LIBRARIES})
add_test(NAME dot_test COMMAND dot_test)

add_executable(elem_test test/elem.cpp)
target_link_libraries(elem_test ${Boost_LIBRARIES})
add_test(NAME elem_test COMMAND elem_test)

add_executable(intersect_test test/intersect.cpp)
target_link_libraries(intersect_test ${Boost_LIBRARIES})
add_test(NAME intersect_test COMMAND intersect_test)

add_executable(is_empty_test test/is_empty.cpp)
target_link_libraries(is_empty_test ${Boost_LIBRARIES})
add_test(NAME is_empty_test COMMAND is_empty_test)

add_executable(length_test test/length.cpp)
target_link_libraries(length_test ${Boost_LIBRARIES})
add_test(NAME length_test COMMAND length_test)

add_executable(make_box_test test/make_box.cpp)
target_link_libraries(make_box_test ${Boost_LIBRARIES})
add_test(NAME make_box_test COMMAND make_box_test)

add_executable(max_test test/max.cpp)
target_link_libraries(max_test ${Boost_LIBRARIES})
add_test(NAME max_test COMMAND max_test)

add_executable(min_test test/min.cpp)
target_link_libraries(min_test ${Boost_LIBRARIES})
add_test(NAME min_test COMMAND min_test)

add_executable(mul_test test/mul.cpp)
target_link_libraries(mul_test ${Boost_LIBRARIES})
add_test(NAME mul_test COMMAND mul_test)

add_executable(mul_operator_test test/mul_operator.cpp)
target_link_libraries(mul_operator_test ${Boost_LIBRARIES})
add_test(NAME mul_operator_test COMMAND mul_operator_test)

add_executable(size_test test/size.cpp)
target_link_libraries(size_test ${Boost_LIBRARIES})
add_test(NAME size_test COMMAND size_test)

add_executable(sub_test test/sub.cpp)
target_link_libraries(sub_test ${Boost_LIBRARIES})
add_test(NAME sub_test COMMAND sub_test)

add_executable(sub_operator_test test/sub_operator.cpp)
target_link_libraries(sub_operator_test ${Boost_LIBRARIES})
add_test(NAME sub_operator_test COMMAND sub_operator_test)

# Adapted tests
# add_executable(std_array_test test/adapted/std_array.cpp)
# target_link_libraries(std_array_test ${Boost_LIBRARIES})
# add_test(NAME std_array_test COMMAND std_array_test)

find_package(CUDA)
if(CUDA_FOUND)
  # GCC 6.0 is the latest version supported by NVCC
  set(CUDA_HOST_COMPILER gcc-6)

  file(COPY test/add.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/add.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/add.cu)
  cuda_add_executable(add_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/add.cu)
  target_link_libraries(add_test_cuda ${Boost_LIBRARIES})
  add_test(NAME add_test_cuda COMMAND add_test_cuda)
  
  file(COPY test/add_operator.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/add_operator.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/add_operator.cu)
  cuda_add_executable(add_operator_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/add_operator.cu)
  target_link_libraries(add_operator_test_cuda ${Boost_LIBRARIES})
  add_test(NAME add_operator_test_cuda COMMAND add_operator_test_cuda)

  file(COPY test/as.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/as.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/as.cu)
  cuda_add_executable(as_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/as.cu)
  target_link_libraries(as_test_cuda ${Boost_LIBRARIES})
  add_test(NAME as_test_cuda COMMAND as_test_cuda)

  file(COPY test/cast.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/cast.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/cast.cu)
  cuda_add_executable(cast_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/cast.cu)
  target_link_libraries(cast_test_cuda ${Boost_LIBRARIES})
  add_test(NAME cast_test_cuda COMMAND cast_test_cuda)

  file(COPY test/contains.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/contains.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/contains.cu)
  cuda_add_executable(contains_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/contains.cu)
  target_link_libraries(contains_test_cuda ${Boost_LIBRARIES})
  add_test(NAME contains_test_cuda COMMAND contains_test_cuda)

  file(COPY test/distance.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/distance.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/distance.cu)
  cuda_add_executable(distance_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/distance.cu)
  target_link_libraries(distance_test_cuda ${Boost_LIBRARIES})
  add_test(NAME distance_test_cuda COMMAND distance_test_cuda)

  file(COPY test/div.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/div.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/div.cu)
  cuda_add_executable(div_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/div.cu)
  target_link_libraries(div_test_cuda ${Boost_LIBRARIES})
  add_test(NAME div_test_cuda COMMAND div_test_cuda)

  file(COPY test/div_operator.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/div_operator.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/div_operator.cu)
  cuda_add_executable(div_operator_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/div_operator.cu)
  target_link_libraries(div_operator_test_cuda ${Boost_LIBRARIES})
  add_test(NAME div_operator_test_cuda COMMAND div_operator_test_cuda)

  file(COPY test/dot.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/dot.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/dot.cu)
  cuda_add_executable(dot_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/dot.cu)
  target_link_libraries(dot_test_cuda ${Boost_LIBRARIES})
  add_test(NAME dot_test_cuda COMMAND dot_test_cuda)

  file(COPY test/elem.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/elem.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/elem.cu)
  cuda_add_executable(elem_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/elem.cu)
  target_link_libraries(elem_test_cuda ${Boost_LIBRARIES})
  add_test(NAME elem_test_cuda COMMAND elem_test_cuda)

  file(COPY test/intersect.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/intersect.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/intersect.cu)
  cuda_add_executable(intersect_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/intersect.cu)
  target_link_libraries(intersect_test_cuda ${Boost_LIBRARIES})
  add_test(NAME intersect_test_cuda COMMAND intersect_test_cuda)

  file(COPY test/is_empty.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/is_empty.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/is_empty.cu)
  cuda_add_executable(is_empty_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/is_empty.cu)
  target_link_libraries(is_empty_test_cuda ${Boost_LIBRARIES})
  add_test(NAME is_empty_test_cuda COMMAND is_empty_test_cuda)

  file(COPY test/length.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/length.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/length.cu)
  cuda_add_executable(length_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/length.cu)
  target_link_libraries(length_test_cuda ${Boost_LIBRARIES})
  add_test(NAME length_test_cuda COMMAND length_test_cuda)

  file(COPY test/make_box.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/make_box.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/make_box.cu)
  cuda_add_executable(make_box_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/make_box.cu)
  target_link_libraries(make_box_test_cuda ${Boost_LIBRARIES})
  add_test(NAME make_box_test_cuda COMMAND make_box_test_cuda)

  file(COPY test/max.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/max.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/max.cu)
  cuda_add_executable(max_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/max.cu)
  target_link_libraries(max_test_cuda ${Boost_LIBRARIES})
  add_test(NAME max_test_cuda COMMAND max_test_cuda)

  file(COPY test/min.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/min.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/min.cu)
  cuda_add_executable(min_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/min.cu)
  target_link_libraries(min_test_cuda ${Boost_LIBRARIES})
  add_test(NAME min_test_cuda COMMAND min_test_cuda)

  file(COPY test/mul.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/mul.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/mul.cu)
  cuda_add_executable(mul_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/mul.cu)
  target_link_libraries(mul_test_cuda ${Boost_LIBRARIES})
  add_test(NAME mul_test_cuda COMMAND mul_test_cuda)

  file(COPY test/mul_operator.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/mul_operator.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/mul_operator.cu)
  cuda_add_executable(mul_operator_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/mul_operator.cu)
  target_link_libraries(mul_operator_test_cuda ${Boost_LIBRARIES})
  add_test(NAME mul_operator_test_cuda COMMAND mul_operator_test_cuda)

  file(COPY test/size.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/size.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/size.cu)
  cuda_add_executable(size_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/size.cu)
  target_link_libraries(size_test_cuda ${Boost_LIBRARIES})
  add_test(NAME size_test_cuda COMMAND size_test_cuda)

  file(COPY test/sub.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/sub.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/sub.cu)
  cuda_add_executable(sub_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/sub.cu)
  target_link_libraries(sub_test_cuda ${Boost_LIBRARIES})
  add_test(NAME sub_test_cuda COMMAND sub_test_cuda)

  file(COPY test/sub_operator.cpp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/cuda)
  file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/sub_operator.cpp ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/sub_operator.cu)
  cuda_add_executable(sub_operator_test_cuda ${CMAKE_CURRENT_BINARY_DIR}/test/cuda/sub_operator.cu)
  target_link_libraries(sub_operator_test_cuda ${Boost_LIBRARIES})
  add_test(NAME sub_operator_test_cuda COMMAND sub_operator_test_cuda)

  # Adapted tests
  # cuda_add_executable(int2_test_cuda test/adapted/cuda/int2.cu)
  # target_link_libraries(int2_test_cuda ${Boost_LIBRARIES})
  # add_test(NAME int2_test_cuda COMMAND int2_test_cuda)

  # cuda_add_executable(int3_test_cuda test/adapted/cuda/int3.cu)
  # target_link_libraries(int3_test_cuda ${Boost_LIBRARIES})
  # add_test(NAME int3_test_cuda COMMAND int3_test_cuda)

  # cuda_add_executable(float2_test_cuda test/adapted/cuda/float2.cu)
  # target_link_libraries(float2_test_cuda ${Boost_LIBRARIES})
  # add_test(NAME float2_test_cuda COMMAND float2_test_cuda)

  # cuda_add_executable(float3_test_cuda test/adapted/cuda/float3.cu)
  # target_link_libraries(float3_test_cuda ${Boost_LIBRARIES})
  # add_test(NAME float3_test_cuda COMMAND float3_test_cuda)

  # cuda_add_executable(thrust_tuple_test_cuda test/adapted/cuda/thrust_tuple.cu)
  # target_link_libraries(thrust_tuple_test_cuda ${Boost_LIBRARIES})
  # add_test(NAME thrust_tuple_test_cuda COMMAND thrust_tuple_test_cuda)

  # cuda_add_executable(thrust_zip_iterator_test_cuda test/adapted/cuda/thrust_zip_iterator.cu)
  # target_link_libraries(thrust_zip_iterator_test_cuda ${Boost_LIBRARIES})
  # add_test(NAME thrust_zip_iterator_test_cuda COMMAND thrust_zip_iterator_test_cuda)
endif()
