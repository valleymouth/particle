// Boost test headers
#pragma push
#pragma diag_suppress = partial_override
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>
#pragma pop

// Particle headers
#include <particle/geometry/adapted/cuda/thrust_zip_iterator.hpp>
#include <particle/geometry/elem.hpp>

// Cuda headers
#include <thrust/host_vector.h>

BOOST_AUTO_TEST_CASE(dim_test)
{
  using particle::geometry::traits::dim;

  thrust::host_vector<int> vec;
  auto x = thrust::make_zip_iterator(
    thrust::make_tuple(vec.begin(), vec.begin(), vec.begin()));
  constexpr int d = dim<decltype(*x)>::value;
  BOOST_CHECK_EQUAL(d, 3);
}

BOOST_AUTO_TEST_CASE(elem_test)
{
  using particle::geometry::elem;

  thrust::host_vector<int> vec0(1, 1);
  thrust::host_vector<int> vec1(1, 2);
  thrust::host_vector<int> vec2(1, 3);

  auto x = thrust::make_zip_iterator(
    thrust::make_tuple(vec0.begin(), vec1.begin(), vec2.begin()));

  BOOST_CHECK_EQUAL(elem<0>(*x), 1);
  BOOST_CHECK_EQUAL(elem<1>(*x), 2);
  BOOST_CHECK_EQUAL(elem<2>(*x), 3);
}
