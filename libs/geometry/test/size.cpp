// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/box.hpp>
#include <particle/geometry/size.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

BOOST_AUTO_TEST_CASE(size_test)
{
  using particle::geometry::box;
  using particle::geometry::size;
  using boost::array;
  using boost::fusion::at_c;
  
  box<array<double, 3>> b = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  auto s = size(b);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(s), 3.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(s), 2.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(s), 6.0, tol);
}
