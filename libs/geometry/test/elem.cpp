// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/elem.hpp>

BOOST_AUTO_TEST_CASE(elem_test)
{
  using particle::geometry::elem;
  
  std::array<int, 3> array = {1, 2, 3};
  BOOST_CHECK_EQUAL(elem<0>(array), 1);
  BOOST_CHECK_EQUAL(elem<1>(array), 2);
  BOOST_CHECK_EQUAL(elem<2>(array), 3);
  elem<0>(array) = 4;
  BOOST_CHECK_EQUAL(elem<0>(array), 4);

  const std::array<int, 3> const_array = {1, 2, 3};
  BOOST_CHECK_EQUAL(elem<0>(const_array), 1);
  BOOST_CHECK_EQUAL(elem<1>(const_array), 2);
  BOOST_CHECK_EQUAL(elem<2>(const_array), 3);
  // Must not compile: assignment of read-only location.
  // elem<0>(array) = 4;
}

BOOST_AUTO_TEST_CASE(elem_rvalue_test)
{
  using particle::geometry::elem;

  // We don't allow calling elem on rvalues.
  // elem<0>(std::array<int, 3>({1, 2, 3}));
}

BOOST_AUTO_TEST_CASE(elem_scalar_test)
{
  using particle::geometry::elem;

  int scalar = 123;
  BOOST_CHECK_EQUAL(elem<0>(scalar), 123);
  BOOST_CHECK_EQUAL(elem<1000>(scalar), 123);
  BOOST_CHECK_EQUAL(elem<1000000>(scalar), 123);
  elem<0>(scalar) = 456;
  BOOST_CHECK_EQUAL(elem<0>(scalar), 456);
  const int const_scalar = 123;
  BOOST_CHECK_EQUAL(elem<0>(const_scalar), 123);
  // Must not compile: assignment of read-only location.
  // elem<0>(const_scalar) = 456;
  int &scalar_ref = scalar;
  BOOST_CHECK_EQUAL(elem<0>(scalar_ref), 456);
}