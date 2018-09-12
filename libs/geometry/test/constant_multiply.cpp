// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/constant_multiply.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

using particle::geometry::operator*;

BOOST_AUTO_TEST_CASE(constant_multiply_test)
{
  using particle::geometry::constant_multiply;
  using boost::fusion::at_c;

  double array0[] = {1.0, 2.0, 3.0};
  auto array1 = constant_multiply(array0, 3);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(array1), 3.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(array1), 6.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(array1), 9.0, tol);
}

BOOST_AUTO_TEST_CASE(constant_multiply_operator_test)
{
  using particle::geometry::constant_multiply;
  using boost::array;
  using boost::fusion::at_c;

  array<double, 3> array0 = {1.0, 2.0, 3.0};
  auto array1 = array0 * 3;
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(array1), 3.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(array1), 6.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(array1), 9.0, tol);

  auto array2 = 4 * array0;
  BOOST_CHECK_CLOSE(at_c<0>(array2), 4.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(array2), 8.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(array2), 12.0, tol);
}
