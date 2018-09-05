// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/contains.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>

BOOST_AUTO_TEST_CASE(contains_test)
{
  using particle::geometry::aabb;
  using particle::geometry::contains;
  using boost::array;

  aabb<array<double, 3>> box = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  array<double, 3> p0 = {-1.0, 4.0, -2.0};
  BOOST_CHECK_EQUAL(contains(box, p0), true);
  array<double, 3> p1 = {-1.0, 1.0, -2.0};
  BOOST_CHECK_EQUAL(contains(box, p1), false);
}
