// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/operators/mul.hpp>

BOOST_AUTO_TEST_CASE(mul_test)
{
  using particle::geometry::elem;
  using particle::geometry::operator*;
  
  std::array<int, 3> array0 = {1, 2, 3};
  std::array<int, 3> array1 = {4, 5, 6};

  {
    auto array3 = array0 * array1;
    BOOST_CHECK_EQUAL(elem<0>(array3), 4);
    BOOST_CHECK_EQUAL(elem<1>(array3), 10);
    BOOST_CHECK_EQUAL(elem<2>(array3), 18);
  }
}

BOOST_AUTO_TEST_CASE(mul_scalar_test)
{
  using particle::geometry::elem;
  using particle::geometry::operator*;
  
  std::array<int, 3> array0 = {1, 2, 3};

  {
    auto array3 = array0 * 10;
    BOOST_CHECK_EQUAL(elem<0>(array3), 10);
    BOOST_CHECK_EQUAL(elem<1>(array3), 20);
    BOOST_CHECK_EQUAL(elem<2>(array3), 30);
  }
}
