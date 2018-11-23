// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/elem.hpp>
#include <particle/geometry/make_box.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(make_box_test)
{
  using particle::geometry::elem;
  using particle::geometry::make_box;

  auto b = make_box(
    vec_type({1, 2, 3})
    , vec_type({4, 5, 6}));
  BOOST_CHECK_EQUAL(elem<0>(b.min), 1);
  BOOST_CHECK_EQUAL(elem<1>(b.min), 2);
  BOOST_CHECK_EQUAL(elem<2>(b.min), 3);
  BOOST_CHECK_EQUAL(elem<0>(b.max), 4);
  BOOST_CHECK_EQUAL(elem<1>(b.max), 5);
  BOOST_CHECK_EQUAL(elem<2>(b.max), 6);
  b.min = {7, 8, 9};
  BOOST_CHECK_EQUAL(elem<0>(b.min), 7);
  BOOST_CHECK_EQUAL(elem<1>(b.min), 8);
  BOOST_CHECK_EQUAL(elem<2>(b.min), 9);
}

BOOST_AUTO_TEST_CASE(make_box_ref_test)
{
  using particle::geometry::elem;
  using particle::geometry::make_box;

  vec_type min = {1, 2, 3};
  vec_type max = {4, 5, 6};
  auto b = make_box(min, max);
  elem<1>(min) = 7;
  elem<1>(max) = 8;
  BOOST_CHECK_EQUAL(elem<0>(b.min), 1);
  BOOST_CHECK_EQUAL(elem<1>(b.min), 7);
  BOOST_CHECK_EQUAL(elem<2>(b.min), 3);
  BOOST_CHECK_EQUAL(elem<0>(b.max), 4);
  BOOST_CHECK_EQUAL(elem<1>(b.max), 8);
  BOOST_CHECK_EQUAL(elem<2>(b.max), 6);
}

BOOST_AUTO_TEST_CASE(make_box_rvalue_test)
{
  using particle::geometry::elem;
  using particle::geometry::make_box;

  auto b = make_box(vec_type({1, 2, 3}), vec_type({4, 5, 6}));
  BOOST_CHECK_EQUAL(elem<0>(b.min), 1);
  BOOST_CHECK_EQUAL(elem<1>(b.min), 2);
  BOOST_CHECK_EQUAL(elem<2>(b.min), 3);
  BOOST_CHECK_EQUAL(elem<0>(b.max), 4);
  BOOST_CHECK_EQUAL(elem<1>(b.max), 5);
  BOOST_CHECK_EQUAL(elem<2>(b.max), 6);
}
