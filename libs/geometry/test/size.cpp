// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/size.hpp>

BOOST_AUTO_TEST_CASE(size_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::size;

  box<std::array<int, 3>, std::array<int, 3>> b = {{-2, 3, -5}, {1, 5, 1}};

  auto s = size(b);

  BOOST_CHECK_EQUAL(elem<0>(s), 3);
  BOOST_CHECK_EQUAL(elem<1>(s), 2);
  BOOST_CHECK_EQUAL(elem<2>(s), 6);
}
