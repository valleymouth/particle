// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/plus.hpp>

// Boost headers
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

BOOST_AUTO_TEST_CASE(plus_test)
{
  using particle::geometry::plus;
  using boost::fusion::at_c;

  double array0[] = {1.0, 2.0, 3.0};
  double array1[] = {4.0, 5.0, 6.0};
  auto array2 = plus(array0, array1);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(array2), 5.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(array2), 7.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(array2), 9.0, tol);
}

BOOST_AUTO_TEST_CASE(plus_plus_test)
{
  using particle::geometry::plus;
  using boost::fusion::at_c;

  double array0[] = {1.0, 2.0, 3.0};
  double array1[] = {4.0, 5.0, 6.0};
  double array2[] = {7.0, 8.0, 9.0};
  auto array3 = plus(array0, plus(array1, array2));
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(array3), 12.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(array3), 15.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(array3), 18.0, tol);
}
