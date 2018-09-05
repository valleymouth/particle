// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/elem.hpp>
#include <particle/geometry/is_empty.hpp>
#include <particle/geometry/contains.hpp>
#include <particle/geometry/min.hpp>
#include <particle/geometry/minus.hpp>
#include <particle/geometry/plus.hpp>
#include <particle/geometry/size.hpp>
#include <particle/geometry/max.hpp>

#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

// Std headers
#include <array>

BOOST_AUTO_TEST_CASE(elem_test)
{
  using particle::geometry::elem;
  std::array<double, 3> array = {1.0, 2.0, 3.0};
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(array), 1.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(array), 2.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(array), 3.0, tol);
}

BOOST_AUTO_TEST_CASE(elem_ref_test)
{
  using particle::geometry::elem;
  std::array<double, 3> array = {1.0, 2.0, 3.0};
  elem<0>(array) = 4.0;
  elem<1>(array) = 5.0;
  elem<2>(array) = 6.0;
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(array), 4.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(array), 5.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(array), 6.0, tol);
}
