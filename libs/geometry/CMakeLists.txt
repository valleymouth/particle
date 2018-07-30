cmake_minimum_required(VERSION 2.6)

# Particle include path 
include_directories(../../)

find_package(Boost REQUIRED system)
include_directories(${BOOST_INCLUDE_DIRS})

#find_package(CUDA)
#if(CUDA_FOUND)
#  set_source_files_properties(src/verlet_list.cpp PROPERTIES CUDA_SOURCE_PROPERTY_FORMAT OBJ)
#endif()
add_executable(elem_test test/elem.cpp)
target_link_libraries(elem_test ${Boost_LIBRARIES})
