// Boost test headers
#pragma push
#pragma diag_suppress = partial_override
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>
#pragma pop

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/operators/add.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(add_test)
{
  using particle::geometry::elem;
  using particle::geometry::operators::operator+;

  vec_type array0 = {1, 2, 3};
  vec_type array1 = {4, 5, 6};
  vec_type array2 = {7, 8, 9};

  {
    auto array3 = array0 + array1;
    BOOST_CHECK_EQUAL(elem<0>(array3), 5);
    BOOST_CHECK_EQUAL(elem<1>(array3), 7);
    BOOST_CHECK_EQUAL(elem<2>(array3), 9);
  }
  {
    auto array3 = array0 + (array1 + array2);
    BOOST_CHECK_EQUAL(elem<0>(array3), 12);
    BOOST_CHECK_EQUAL(elem<1>(array3), 15);
    BOOST_CHECK_EQUAL(elem<2>(array3), 18);
  }
  {
    auto array3 = (array0 + array1) + array2;
    BOOST_CHECK_EQUAL(elem<0>(array3), 12);
    BOOST_CHECK_EQUAL(elem<1>(array3), 15);
    BOOST_CHECK_EQUAL(elem<2>(array3), 18);
  }
  {
    auto array3 = (array0 + array2) + (array1 + array2);
    BOOST_CHECK_EQUAL(elem<0>(array3), 19);
    BOOST_CHECK_EQUAL(elem<1>(array3), 23);
    BOOST_CHECK_EQUAL(elem<2>(array3), 27);
  }
}

BOOST_AUTO_TEST_CASE(add_scalar_test)
{
  using particle::geometry::elem;
  using particle::geometry::operators::operator+;

  vec_type array0 = {1, 2, 3};
  vec_type array1 = {4, 5, 6};

  {
    auto array3 = array0 + 10;
    BOOST_CHECK_EQUAL(elem<0>(array3), 11);
    BOOST_CHECK_EQUAL(elem<1>(array3), 12);
    BOOST_CHECK_EQUAL(elem<2>(array3), 13);
  }
  {
    auto array3 = array0 + (array1 + 10);
    BOOST_CHECK_EQUAL(elem<0>(array3), 15);
    BOOST_CHECK_EQUAL(elem<1>(array3), 17);
    BOOST_CHECK_EQUAL(elem<2>(array3), 19);
  }
}
