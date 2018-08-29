// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/size.hpp>

// Std headers
#include <array>

BOOST_AUTO_TEST_CASE(size_test)
{
  using particle::geometry::aabb;
  using particle::geometry::elem;
  using particle::geometry::size;

  aabb<std::array<double, 3>> box(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  std::array<double, 3> s = size(box);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(s), 3.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(s), 2.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(s), 6.0, tol);
}
