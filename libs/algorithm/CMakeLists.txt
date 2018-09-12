cmake_minimum_required(VERSION 2.6)

# Particle include path 
include_directories(../../)

find_package(Boost REQUIRED system)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(for_each_test test/for_each.cpp)
target_link_libraries(for_each_test ${Boost_LIBRARIES})
target_compile_options(for_each_test PUBLIC --expt-extended-lambda --std=c++14)
add_test(NAME for_each_test COMMAND for_each_test)
