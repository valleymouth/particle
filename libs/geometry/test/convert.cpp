// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/convert.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

BOOST_AUTO_TEST_CASE(convert_test)
{
  using particle::geometry::convert;
  using boost::array;
  using boost::fusion::at_c;

  array<double, 3> array0 = {3.25, 6.50, 9.75};
  auto array1 = convert<int>(array0);
  BOOST_CHECK_EQUAL(at_c<0>(array1), 3);
  BOOST_CHECK_EQUAL(at_c<1>(array1), 6);
  BOOST_CHECK_EQUAL(at_c<2>(array1), 9);
}
