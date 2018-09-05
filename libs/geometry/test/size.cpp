// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/size.hpp>
#include <particle/geometry/is_aabb.hpp>
#include <particle/geometry/is_vector.hpp>
// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

BOOST_AUTO_TEST_CASE(size_test)
{
  using particle::geometry::aabb;
  using particle::geometry::size;
  using boost::array;
  using boost::fusion::at_c;

  using particle::geometry::traits::is_vector;
  std::cout << is_vector<array<double, 3>>::value << std::endl;
  std::cout << is_vector<int>::value << std::endl;
  
  aabb<array<double, 3>> box = {{-2.0, 3.0, -5.0}, {1.0, 5.0, 1.0}};
  auto s = size(box);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(at_c<0>(s), 3.0, tol);
  BOOST_CHECK_CLOSE(at_c<1>(s), 2.0, tol);
  BOOST_CHECK_CLOSE(at_c<2>(s), 6.0, tol);
}
