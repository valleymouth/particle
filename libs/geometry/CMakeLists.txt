cmake_minimum_required(VERSION 2.6)

# Particle include path 
include_directories(../../)

find_package(Boost REQUIRED system)
include_directories(${BOOST_INCLUDE_DIRS})

find_package(CUDA)
if(CUDA_FOUND)
  set_source_files_properties(src/verlet_list.cpp PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
endif()

add_executable(elem_test test/elem.cpp)
target_link_libraries(elem_test ${Boost_LIBRARIES})
add_test(NAME elem_test COMMAND elem_test)

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

add_executable(equal_test test/equal.cpp)
target_link_libraries(equal_test ${Boost_LIBRARIES})
add_test(NAME equal_test COMMAND equal_test)
