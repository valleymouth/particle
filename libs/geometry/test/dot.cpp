// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/dot.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(add_test)
{
  using particle::geometry::dot;

  vec_type array0 = {1, 2, 3};
  vec_type array1 = {4, 5, 6};

  BOOST_CHECK_EQUAL(dot(array0, array1), 32);
  BOOST_CHECK_EQUAL(dot(array0, vec_type({4, 5, 6})), 32);
}

