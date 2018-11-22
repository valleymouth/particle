// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/intersect.hpp>

BOOST_AUTO_TEST_CASE(intersect_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::intersect;
  using particle::geometry::max;
  using particle::geometry::min;

  using vec_type = std::array<int, 3>;
  using box_type = box<vec_type, vec_type>;
 
  box_type b0 = {{-2, -3, -4}, {2, 3, 4}};
  box_type b1 = {{-1, 0, -5}, {3, 5, 5}};

  {
    auto b3 = intersect(b0, b1);
    BOOST_CHECK_EQUAL(elem<0>(min(b3)), -1);
    BOOST_CHECK_EQUAL(elem<1>(min(b3)), 0);
    BOOST_CHECK_EQUAL(elem<2>(min(b3)), -4);
    BOOST_CHECK_EQUAL(elem<0>(max(b3)), 2);
    BOOST_CHECK_EQUAL(elem<1>(max(b3)), 3);
    BOOST_CHECK_EQUAL(elem<2>(max(b3)), 4);
  }
  {
    auto b3 = intersect(
      b0
      , box_type { vec_type({-1, 0, -5}), vec_type({3, 5, 5}) });
    BOOST_CHECK_EQUAL(elem<0>(min(b3)), -1);
    BOOST_CHECK_EQUAL(elem<1>(min(b3)), 0);
    BOOST_CHECK_EQUAL(elem<2>(min(b3)), -4);
    BOOST_CHECK_EQUAL(elem<0>(max(b3)), 2);
    BOOST_CHECK_EQUAL(elem<1>(max(b3)), 3);
    BOOST_CHECK_EQUAL(elem<2>(max(b3)), 4);
  }
}
