// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/box.hpp>
#include <particle/geometry/max.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

BOOST_AUTO_TEST_CASE(max_test)
{
  using particle::geometry::box;
  using particle::geometry::max;
  using boost::array;
  using boost::fusion::at_c;
  
  box<array<double, 3>> b = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  auto u = max(b);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(u), 1.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(u), 5.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(u), 1.0, tol);
}

BOOST_AUTO_TEST_CASE(max_ref_test)
{
  using particle::geometry::box;
  using particle::geometry::max;
  using boost::array;
  using boost::fusion::at_c;
  
  box<array<double, 3>> b = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  max(b) = {2.0, 4.0, 3.0};
  auto u = max(b);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(u), 2.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(u), 4.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(u), 3.0, tol);
}
