// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/contains.hpp>

BOOST_AUTO_TEST_CASE(contains_test)
{
  using particle::geometry::box;
  using particle::geometry::contains;

  box<std::array<int, 3>, std::array<int, 3>> b = {{-2, 3, -5}, {1, 5, 1}};
  std::array<int, 3> p0 = {-1, 4, -2};
  BOOST_CHECK_EQUAL(contains(b, p0), true);
  std::array<int, 3> p1 = {-1, 1, -2};
  BOOST_CHECK_EQUAL(contains(b, p1), false);
}
