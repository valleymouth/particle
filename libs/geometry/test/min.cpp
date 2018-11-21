// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/min.hpp>

BOOST_AUTO_TEST_CASE(min_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::min;
  {
    box<std::array<int, 3>, std::array<int, 3>> b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
    min(b) = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 9);
  }
  {
    box<std::array<int, 3>, std::array<int, 3>> const b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
  }
}

BOOST_AUTO_TEST_CASE(min_ref_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::min;
  {
    std::array<int, 3> array = {1, 2, 3};
    box<std::array<int, 3>&, std::array<int, 3>> b = {array, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
    array = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 9);
  }
  {
    std::array<int, 3> const array = {1, 2, 3};
    box<std::array<int, 3> const&, std::array<int, 3>> b = {array, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
    // Must not compile.
    // min(b) = {7, 8, 9};
  }
}
