// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/operators/sdiv.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

using particle::geometry::operator/;

BOOST_AUTO_TEST_CASE(sdiv_test)
{
  using particle::geometry::sdiv;
  using boost::fusion::at_c;

  double array0[] = {3.0, 6.0, 9.0};
  auto array1 = sdiv(array0, 3);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(array1), 1.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(array1), 2.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(array1), 3.0, tol);
}

BOOST_AUTO_TEST_CASE(sdiv_operator_test)
{
  using particle::geometry::sdiv;
  using boost::array;
  using boost::fusion::at_c;

  array<double, 3> array0 = {3.0, 6.0, 9.0};
  auto array1 = array0 / 3;
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(array1), 1.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(array1), 2.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(array1), 3.0, tol);
}
