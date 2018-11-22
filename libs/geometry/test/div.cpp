// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/div.hpp>

BOOST_AUTO_TEST_CASE(div_test)
{
  using particle::geometry::elem;
  using particle::geometry::div;
  
  std::array<int, 3> array0 = {4, 9, 20};
  std::array<int, 3> array1 = {2, 3, 5};

  {
    auto array3 = div(array0, array1);
    BOOST_CHECK_EQUAL(elem<0>(array3), 2);
    BOOST_CHECK_EQUAL(elem<1>(array3), 3);
    BOOST_CHECK_EQUAL(elem<2>(array3), 4);
  }
}

BOOST_AUTO_TEST_CASE(div_scalar_test)
{
  using particle::geometry::elem;
  using particle::geometry::div;
  
  std::array<int, 3> array0 = {10, 100, 1000};

  {
    auto array3 = div(array0, 10);
    BOOST_CHECK_EQUAL(elem<0>(array3), 1);
    BOOST_CHECK_EQUAL(elem<1>(array3), 10);
    BOOST_CHECK_EQUAL(elem<2>(array3), 100);
  }
}
