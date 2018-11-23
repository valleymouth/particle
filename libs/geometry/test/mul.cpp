// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/mul.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(mul_test)
{
  using particle::geometry::elem;
  using particle::geometry::mul;
  
  vec_type array0 = {1, 2, 3};
  vec_type array1 = {4, 5, 6};

  {
    auto array3 = mul(array0, array1);
    BOOST_CHECK_EQUAL(elem<0>(array3), 4);
    BOOST_CHECK_EQUAL(elem<1>(array3), 10);
    BOOST_CHECK_EQUAL(elem<2>(array3), 18);
  }
}

BOOST_AUTO_TEST_CASE(mul_scalar_test)
{
  using particle::geometry::elem;
  using particle::geometry::mul;
  
  vec_type array0 = {1, 2, 3};

  {
    auto array3 = mul(array0, 10);
    BOOST_CHECK_EQUAL(elem<0>(array3), 10);
    BOOST_CHECK_EQUAL(elem<1>(array3), 20);
    BOOST_CHECK_EQUAL(elem<2>(array3), 30);
  }
}
