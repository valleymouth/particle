// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/equal.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

struct triple
{
  typedef int result_type;

  int operator()(int t) const
  {
    return 3 * t;
  }
};

BOOST_AUTO_TEST_CASE(equal_vector_test)
{
  using boost::array;

  {
    array<int, 3> v0 = {1, 2, 3};
    array<int, 3> v1 = {1, 2, 3};
    array<int, 3> v2 = {1, 1, 3};
    BOOST_CHECK_EQUAL(particle::geometry::equal(v0, v1), true);
    BOOST_CHECK_EQUAL(particle::geometry::equal(v1, v2), false);
  }

  {
    using boost::fusion::transform;
    
    array<int, 3> v0 = {1, 2, 3};
    array<int, 3> v1 = {3, 6, 9};
    BOOST_CHECK_EQUAL(particle::geometry::equal(transform(v0, triple()), v1), true);
  }
}

BOOST_AUTO_TEST_CASE(equal_aabb_test)
{
  using particle::geometry::aabb;
  using boost::array;

  aabb<array<int, 3>> box0 = {{-2, 3, -5}, {1, 5, 1}};
  aabb<array<int, 3>> box1 = {{-2, 3, -5}, {1, 5, 1}};
  aabb<array<int, 3>> box2 = {{-2, 3, -5}, {1, 4, 1}};
  BOOST_CHECK_EQUAL(particle::geometry::equal(box0, box1), true);
  BOOST_CHECK_EQUAL(particle::geometry::equal(box1, box2), false);
}
