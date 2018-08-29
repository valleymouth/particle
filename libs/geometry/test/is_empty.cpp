// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/is_empty.hpp>

// Std headers
#include <array>

BOOST_AUTO_TEST_CASE(is_empty_test)
{
  using particle::geometry::aabb;
  using particle::geometry::is_empty;

  aabb<std::array<double, 3>> box0(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  BOOST_CHECK_EQUAL(is_empty(box0), false);

  aabb<std::array<double, 3>> box1(
    {-2.0, 3.0, -5.0}
    , {1.0, 2.0, 1.0});
  BOOST_CHECK_EQUAL(is_empty(box1), true);
}
