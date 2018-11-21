// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/max.hpp>

BOOST_AUTO_TEST_CASE(max_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::max;
  {
    box<std::array<int, 3>, std::array<int, 3>> b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
    max(b) = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 9);
  }
  {
    box<std::array<int, 3>, std::array<int, 3>> const b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
  }
}

BOOST_AUTO_TEST_CASE(max_ref_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::max;
  {
    std::array<int, 3> array = {4, 5, 6};
    box<std::array<int, 3>, std::array<int, 3>&> b = {{1, 2, 3}, array};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
    array = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 9);
  }
  {
    std::array<int, 3> const array = {4, 5, 6};
    box<std::array<int, 3>, std::array<int, 3> const&> b = {{1, 2, 3}, array};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
    // Must not compile.
    // max(b) = {7, 8, 9};
  }
}
