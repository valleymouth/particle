// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/is_aabb.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>

BOOST_AUTO_TEST_CASE(is_vector_test)
{
  using particle::geometry::aabb;
  using particle::geometry::traits::is_aabb;
  using boost::array;
  
  BOOST_CHECK_EQUAL((is_aabb<aabb<array<double, 3>>>::value), true);
  BOOST_CHECK_EQUAL(is_aabb<int>::value, false);
}
