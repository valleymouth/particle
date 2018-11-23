// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/operators/div.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(div_test)
{
  using particle::geometry::elem;
  using particle::geometry::operator/;
  
  vec_type array0 = {4, 9, 20};
  vec_type array1 = {2, 3, 5};

  {
    auto array3 = array0 / array1;
    BOOST_CHECK_EQUAL(elem<0>(array3), 2);
    BOOST_CHECK_EQUAL(elem<1>(array3), 3);
    BOOST_CHECK_EQUAL(elem<2>(array3), 4);
  }
}

BOOST_AUTO_TEST_CASE(div_scalar_test)
{
  using particle::geometry::elem;
  using particle::geometry::operator/;
  
  vec_type array0 = {10, 100, 1000};

  {
    auto array3 = array0 / 10;
    BOOST_CHECK_EQUAL(elem<0>(array3), 1);
    BOOST_CHECK_EQUAL(elem<1>(array3), 10);
    BOOST_CHECK_EQUAL(elem<2>(array3), 100);
  }
}
