cmake_minimum_required(VERSION 2.6)

# Particle include path 
include_directories(../../)

find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

#find_package(CUDA)
#if(CUDA_FOUND)
  # GCC 6.0 is the latest version supported by NVCC
#  set(CUDA_HOST_COMPILER gcc-6)
#endif()

add_executable(elem_test test/elem.cpp)
target_link_libraries(elem_test ${Boost_LIBRARIES})
add_test(NAME elem_test COMMAND elem_test)

add_executable(add_test test/add.cpp)
target_link_libraries(add_test ${Boost_LIBRARIES})
add_test(NAME add_test COMMAND add_test)

add_executable(sub_test test/sub.cpp)
target_link_libraries(sub_test ${Boost_LIBRARIES})
add_test(NAME sub_test COMMAND sub_test)

add_executable(min_test test/min.cpp)
target_link_libraries(min_test ${Boost_LIBRARIES})
add_test(NAME min_test COMMAND min_test)

add_executable(max_test test/max.cpp)
target_link_libraries(max_test ${Boost_LIBRARIES})
add_test(NAME max_test COMMAND max_test)

add_executable(is_empty_test test/is_empty.cpp)
target_link_libraries(is_empty_test ${Boost_LIBRARIES})
add_test(NAME is_empty_test COMMAND is_empty_test)

add_executable(contains_test test/contains.cpp)
target_link_libraries(contains_test ${Boost_LIBRARIES})
add_test(NAME contains_test COMMAND contains_test)

add_executable(size_test test/size.cpp)
target_link_libraries(size_test ${Boost_LIBRARIES})
add_test(NAME size_test COMMAND size_test)

add_executable(add_operator_test test/add_operator.cpp)
target_link_libraries(add_operator_test ${Boost_LIBRARIES})
add_test(NAME add_operator_test COMMAND add_operator_test)

add_executable(sub_operator_test test/sub_operator.cpp)
target_link_libraries(sub_operator_test ${Boost_LIBRARIES})
add_test(NAME sub_operator_test COMMAND sub_operator_test)

add_executable(make_box_test test/make_box.cpp)
target_link_libraries(make_box_test ${Boost_LIBRARIES})
add_test(NAME make_box_test COMMAND make_box_test)
