// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/operators/sub.hpp>

BOOST_AUTO_TEST_CASE(sub_test)
{
  using particle::geometry::elem;
  using particle::geometry::operator-;
  
  std::array<int, 3> array0 = {1, 2, 3};
  std::array<int, 3> array1 = {4, 5, 6};
  std::array<int, 3> array2 = {7, 8, 9};

  {
    auto array3 = array0 - array1;
    BOOST_CHECK_EQUAL(elem<0>(array3), -3);
    BOOST_CHECK_EQUAL(elem<1>(array3), -3);
    BOOST_CHECK_EQUAL(elem<2>(array3), -3);
  }
  {
    auto array3 = array0 - (array1 - array2);
    BOOST_CHECK_EQUAL(elem<0>(array3), 4);
    BOOST_CHECK_EQUAL(elem<1>(array3), 5);
    BOOST_CHECK_EQUAL(elem<2>(array3), 6);
  }
  {
    auto array3 = (array0 - array1) - array2;
    BOOST_CHECK_EQUAL(elem<0>(array3), -10);
    BOOST_CHECK_EQUAL(elem<1>(array3), -11);
    BOOST_CHECK_EQUAL(elem<2>(array3), -12);
  }
  {
    auto array3 = (array0 - array2) - (array1 - array2);
    BOOST_CHECK_EQUAL(elem<0>(array3), -3);
    BOOST_CHECK_EQUAL(elem<1>(array3), -3);
    BOOST_CHECK_EQUAL(elem<2>(array3), -3);
  }
}

BOOST_AUTO_TEST_CASE(sub_scalar_test)
{
  using particle::geometry::elem;
  using particle::geometry::operator-;

  std::array<int, 3> array0 = {1, 2, 3};
  std::array<int, 3> array1 = {4, 5, 6};

  {
    auto array3 = array0 - 10;
    BOOST_CHECK_EQUAL(elem<0>(array3), -9);
    BOOST_CHECK_EQUAL(elem<1>(array3), -8);
    BOOST_CHECK_EQUAL(elem<2>(array3), -7);
  }
  {
    auto array3 = array0 - (array1 - 10);
    BOOST_CHECK_EQUAL(elem<0>(array3), 7);
    BOOST_CHECK_EQUAL(elem<1>(array3), 7);
    BOOST_CHECK_EQUAL(elem<2>(array3), 7);
  }
}
