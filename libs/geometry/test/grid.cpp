// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/algorithm/for_each.hpp>
#include <particle/geometry/box.hpp>
#include <particle/left.hpp>
#include <particle/grid/right.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/sequence/io.hpp>

#include <vector>
#include <iostream>

using boost::fusion::operator<<;

BOOST_AUTO_TEST_CASE(grid_test)
{
  using particle::geometry::box;
  using particle::for_each;
  using particle::left;
  using particle::right;
  using boost::array;

  {
    box<array<int, 2>> b = {{-1, -2}, {3, 2}};
    array<int, 2> cell = {1, 1};
    BOOST_CHECK_EQUAL(left<std::size_t>(cell, b), 14);
  }

  {
    box<array<int, 2>> b0 = {{-1, -2}, {3, 2}};
    box<array<int, 2>> b1 = {{-1, 0}, {1, 2}};
    std::vector<array<int, 3>> output;
    for_each(b1, [&](auto i, auto j) { std::cout << left<std::size_t, array<int, 2>>({i, j}, b0) << std::endl; });

    // for (int i = 1; i < 3; i++)
    // {
    //   for (int j = 0; j < 2; j++)
    //   {
    //     std::size_t index = (k - 3) + (j - 2) * 3 + (i + 1) * 6;
    //     BOOST_CHECK_EQUAL(output[index][0], i);
    //     BOOST_CHECK_EQUAL(output[index][1], j);
    //     BOOST_CHECK_EQUAL(output[index][2], k);
    //   }
    // }
    
//    BOOST_CHECK_EQUAL(particle::left<std::size_t>(index, size), 5 + 3 * 10 + 25 * 10 * 20);
  }

  {
    box<array<int, 2>> b0 = {{-1, -2}, {3, 2}};
    box<array<int, 2>> b1 = {{-1, 0}, {1, 2}};
    std::vector<array<int, 3>> output;
    for_each(b1, [&](auto i, auto j) { std::cout << right<std::size_t, array<int, 2>>({i, j}, b0) << std::endl; });
  }
}
