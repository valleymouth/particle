// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/max.hpp>

// Std headers
#include <array>

BOOST_AUTO_TEST_CASE(max_test)
{
  using particle::geometry::aabb;
  using particle::geometry::elem;
  using particle::geometry::max;
  
  aabb<std::array<double, 3>> box(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  std::array<double, 3> u = max(box);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(u), 1.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(u), 5.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(u), 1.0, tol);
}
