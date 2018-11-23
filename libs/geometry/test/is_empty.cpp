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
#include <particle/geometry/is_empty.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(is_empty_test)
{
  using particle::geometry::box;
  using particle::geometry::is_empty;

  box<vec_type, vec_type> box0 = {{-2, 3, -5}, {1, 5, 1}};
  BOOST_CHECK_EQUAL(is_empty(box0), false);

  box<vec_type, vec_type> box1 = {{-2, 3, -5}, {1, 2, 1}};
  BOOST_CHECK_EQUAL(is_empty(box1), true);
}
