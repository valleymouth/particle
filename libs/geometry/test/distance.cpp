// Boost test headers
#pragma push
#pragma diag_suppress = partial_override
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>
#pragma pop

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int2.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/distance.hpp>

#ifdef __CUDACC__
using vec_type = int2;
#else
using vec_type = std::array<int, 2>;
#endif

BOOST_AUTO_TEST_CASE(add_test)
{
  using particle::geometry::distance;
  vec_type array0 = {1, 2};
  vec_type array1 = {4, 6};

  BOOST_CHECK_EQUAL(distance(array0, array1), 5);
  BOOST_CHECK_EQUAL(distance(array0, vec_type({4, 6})), 5);
}

