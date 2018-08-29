// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/minus.hpp>

// Std headers
#include <array>

BOOST_AUTO_TEST_CASE(minus_test)
{
  using particle::geometry::elem;
  using particle::geometry::minus;

  std::array<double, 3> array0 = {1.0, 2.0, 3.0};
  std::array<double, 3> array1 = {4.0, 5.0, 6.0};
  std::array<double, 3> array3 = minus(array0, array1);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(array3), -3.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(array3), -3.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(array3), -3.0, tol);
}
