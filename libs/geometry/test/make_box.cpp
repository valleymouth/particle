// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/make_box.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>

BOOST_AUTO_TEST_CASE(make_box_test)
{
  using particle::geometry::make_box;
  using boost::array;
  using boost::fusion::at_c;

  auto b = make_box(
    array<double, 3>({1.0, 2.0, 3.0})
    , array<double, 3>({4.0, 5.0, 6.0}));
  BOOST_CHECK_EQUAL(b.min == (array<double, 3>({1.0, 2.0, 3.0})), true);
  BOOST_CHECK_EQUAL(b.min == (array<double, 3>({4.0, 5.0, 6.0})), false);
}
