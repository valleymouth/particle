// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/min.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

BOOST_AUTO_TEST_CASE(min_test)
{
  using particle::geometry::aabb;
  using particle::geometry::min;
  using boost::array;
  using boost::fusion::at_c;

  aabb<array<double, 3>> box = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  auto l = min(box);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(l), -2.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(l), 3.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(l), -5.0, tol);
}
