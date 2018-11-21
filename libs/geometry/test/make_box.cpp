// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/make_box.hpp>

BOOST_AUTO_TEST_CASE(make_box_test)
{
  using particle::geometry::make_box;

  auto b = make_box(
    std::array<int, 3>({1, 2, 3})
    , std::array<int, 3>({4, 5, 6}));
  BOOST_CHECK_EQUAL(b.min == (std::array<int, 3>({1, 2, 3})), true);
  BOOST_CHECK_EQUAL(b.max == (std::array<int, 3>({4, 5, 6})), true);
}

BOOST_AUTO_TEST_CASE(make_box_ref_test)
{
  using particle::geometry::make_box;

  std::array<int, 3> min = {1, 2, 3};
  std::array<int, 3> max = {4, 5, 6};
  auto b = make_box(min, max);
  min[1] = 7;
  max[1] = 8;
  BOOST_CHECK_EQUAL(b.min == (std::array<int, 3>({1, 7, 3})), true);
  BOOST_CHECK_EQUAL(b.max == (std::array<int, 3>({4, 8, 6})), true);
}
