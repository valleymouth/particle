// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/box.hpp>
#include <particle/geometry/contains.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(contains_test)
{
  using particle::geometry::box;
  using particle::geometry::contains;

  box<vec_type, vec_type> b = {{-2, 3, -5}, {1, 5, 1}};
  vec_type p0 = {-1, 4, -2};
  BOOST_CHECK_EQUAL(contains(b, p0), true);
  vec_type p1 = {-1, 1, -2};
  BOOST_CHECK_EQUAL(contains(b, p1), false);
}
