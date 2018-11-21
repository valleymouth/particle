// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/is_empty.hpp>

BOOST_AUTO_TEST_CASE(is_empty_test)
{
  using particle::geometry::box;
  using particle::geometry::is_empty;

  box<std::array<double, 3>, std::array<double, 3>> box0 = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  BOOST_CHECK_EQUAL(is_empty(box0), false);

  box<std::array<double, 3>, std::array<double, 3>> box1 = {{-2.0, 3.0, -5.0}, {1.0, 2.0, 1.0}};
  BOOST_CHECK_EQUAL(is_empty(box1), true);
}
