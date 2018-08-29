// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/equal.hpp>

// Std headers
#include <array>

BOOST_AUTO_TEST_CASE(equal_vector_test)
{
  using particle::geometry::equal;

  std::array<int, 3> v0 = {1, 2, 3};
  std::array<int, 3> v1 = {1, 2, 3};
  std::array<int, 3> v2 = {1, 1, 3};
  BOOST_CHECK_EQUAL(equal(v0, v1), true);
  BOOST_CHECK_EQUAL(equal(v1, v2), false);
}

BOOST_AUTO_TEST_CASE(equal_aabb_test)
{
  using particle::geometry::aabb;
  using particle::geometry::equal;

  aabb<std::array<int, 3>> box0(
    {-2, 3, -5}
    , {1, 5, 1});
  aabb<std::array<int, 3>> box1(
    {-2, 3, -5}
    , {1, 5, 1});
  aabb<std::array<int, 3>> box2(
    {-2, 3, -5}
    , {1, 4, 1});
  BOOST_CHECK_EQUAL(equal(box0, box1), true);
  BOOST_CHECK_EQUAL(equal(box1, box2), false);
}
