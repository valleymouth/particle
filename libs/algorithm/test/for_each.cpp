// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/algorithm/for_each.hpp>
#include <particle/geometry/box.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/io.hpp>

// Std headers
#include <vector>

BOOST_AUTO_TEST_CASE(for_each_test)
{
  using boost::array;
  using particle::for_each;
  using particle::geometry::box;
  
  box<array<int, 3>> b({-1, 2, 3}, {1, 4, 6});
  std::vector<array<int, 3>> output;
  for_each(b, [&](auto i, auto j, auto k) { output.push_back({i, j, k}); });

  for (int i = -1; i < 1; i++)
  {
    for (int j = 2; j < 4; j++)
    {
      for (int k = 3; k < 6; k++)
      {
        std::size_t index = (k - 3) + (j - 2) * 3 + (i + 1) * 6;
        BOOST_CHECK_EQUAL(output[index][0], i);
        BOOST_CHECK_EQUAL(output[index][1], j);
        BOOST_CHECK_EQUAL(output[index][2], k);
      }
    }
  }
}
