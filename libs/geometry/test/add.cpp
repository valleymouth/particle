// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/add.hpp>

BOOST_AUTO_TEST_CASE(add_test)
{
  using particle::geometry::add;
  using particle::geometry::elem;

  std::array<int, 3> array0 = {1, 2, 3};
  std::array<int, 3> array1 = {4, 5, 6};
  std::array<int, 3> array2 = {7, 8, 9};

  {
    auto array3 = add(array0, array1);
    BOOST_CHECK_EQUAL(elem<0>(array3), 5);
    BOOST_CHECK_EQUAL(elem<1>(array3), 7);
    BOOST_CHECK_EQUAL(elem<2>(array3), 9);
  }
  {
    auto array3 = add(array0, add(array1, array2));
    BOOST_CHECK_EQUAL(elem<0>(array3), 12);
    BOOST_CHECK_EQUAL(elem<1>(array3), 15);
    BOOST_CHECK_EQUAL(elem<2>(array3), 18);
  }
  {
    auto array3 = add(add(array0, array1), array2);
    BOOST_CHECK_EQUAL(elem<0>(array3), 12);
    BOOST_CHECK_EQUAL(elem<1>(array3), 15);
    BOOST_CHECK_EQUAL(elem<2>(array3), 18);
  }
  {
    auto array3 = add(add(array0, array2), add(array1, array2));
    BOOST_CHECK_EQUAL(elem<0>(array3), 19);
    BOOST_CHECK_EQUAL(elem<1>(array3), 23);
    BOOST_CHECK_EQUAL(elem<2>(array3), 27);
  }
}

BOOST_AUTO_TEST_CASE(add_scalar_test)
{
  using particle::geometry::add;
  using particle::geometry::elem;

  std::array<int, 3> array0 = {1, 2, 3};
  std::array<int, 3> array1 = {4, 5, 6};

  {
    auto array3 = add(array0, 10);
    BOOST_CHECK_EQUAL(elem<0>(array3), 11);
    BOOST_CHECK_EQUAL(elem<1>(array3), 12);
    BOOST_CHECK_EQUAL(elem<2>(array3), 13);
  }
  {
    auto array3 = add(array0, add(array1, 10));
    BOOST_CHECK_EQUAL(elem<0>(array3), 15);
    BOOST_CHECK_EQUAL(elem<1>(array3), 17);
    BOOST_CHECK_EQUAL(elem<2>(array3), 19);
  }
}
