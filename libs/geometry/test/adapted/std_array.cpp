// Boost test headers
#pragma push
#pragma diag_suppress = partial_override
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>
#pragma pop

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/elem.hpp>

BOOST_AUTO_TEST_CASE(dim_test)
{
  using particle::geometry::traits::dim;

  {
    constexpr int d = dim<std::array<int, 2>>::value;
    BOOST_CHECK_EQUAL(d, 2);
  }
  {
    constexpr int d = dim<std::array<int, 3>>::value;
    BOOST_CHECK_EQUAL(d, 3);
  }
}

BOOST_AUTO_TEST_CASE(elem_test)
{
  using particle::geometry::elem;

  using vec_type = std::array<int, 3>;
  
  vec_type array = {1, 2, 3};

  BOOST_CHECK_EQUAL(elem<0>(array), 1);
  BOOST_CHECK_EQUAL(elem<1>(array), 2);
  BOOST_CHECK_EQUAL(elem<2>(array), 3);
}
