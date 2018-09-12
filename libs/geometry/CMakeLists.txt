cmake_minimum_required(VERSION 2.6)

# Particle include path 
include_directories(../../)

find_package(Boost REQUIRED system)
include_directories(${BOOST_INCLUDE_DIRS})

find_package(CUDA)
if(CUDA_FOUND)
  set_source_files_properties(src/verlet_list.cpp PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
endif()

add_executable(plus_test test/plus.cpp)
target_link_libraries(plus_test ${Boost_LIBRARIES})
add_test(NAME plus_test COMMAND plus_test)

add_executable(minus_test test/minus.cpp)
target_link_libraries(minus_test ${Boost_LIBRARIES})
add_test(NAME minus_test COMMAND minus_test)

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

add_executable(plus_operator_test test/plus_operator.cpp)
target_link_libraries(plus_operator_test ${Boost_LIBRARIES})
add_test(NAME plus_operator_test COMMAND plus_operator_test)

add_executable(minus_operator_test test/minus_operator.cpp)
target_link_libraries(minus_operator_test ${Boost_LIBRARIES})
add_test(NAME minus_operator_test COMMAND minus_operator_test)

add_executable(make_box_test test/make_box.cpp)
target_link_libraries(make_box_test ${Boost_LIBRARIES})
add_test(NAME make_box_test COMMAND make_box_test)

add_executable(constant_multiply_test test/constant_multiply.cpp)
target_link_libraries(constant_multiply_test ${Boost_LIBRARIES})
add_test(NAME constant_multiply_test COMMAND constant_multiply_test)

add_executable(constant_divide_test test/constant_divide.cpp)
target_link_libraries(constant_divide_test ${Boost_LIBRARIES})
add_test(NAME constant_divide_test COMMAND constant_divide_test)

add_executable(convert_test test/convert.cpp)
target_link_libraries(convert_test ${Boost_LIBRARIES})
add_test(NAME convert_test COMMAND convert_test)

# add_executable(grid_test test/grid.cpp)
# target_link_libraries(grid_test ${Boost_LIBRARIES})
# add_test(NAME grid_test COMMAND grid_test)
