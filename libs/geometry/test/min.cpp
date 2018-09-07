// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/box.hpp>
#include <particle/geometry/min.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

BOOST_AUTO_TEST_CASE(min_test)
{
  using particle::geometry::box;
  using particle::geometry::min;
  using boost::array;
  using boost::fusion::at_c;

  box<array<double, 3>> b = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  auto l = min(b);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(l), -2.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(l), 3.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(l), -5.0, tol);
}

BOOST_AUTO_TEST_CASE(min_ref_test)
{
  using particle::geometry::box;
  using particle::geometry::min;
  using boost::array;
  using boost::fusion::at_c;

  box<array<double, 3>> b = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  min(b) = {-3.0, 0.0, -6.0};
  auto l = min(b);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(l), -3.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(l), 0.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(l), -6.0, tol);
}
