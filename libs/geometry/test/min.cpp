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
#include <particle/geometry/box.hpp>
#include <particle/geometry/min.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(min_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::min;
  {
    box<vec_type, vec_type> b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
    min(b) = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 9);
  }
  {
    box<vec_type, vec_type> const b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
    // Must give a compilation error
    // min(b) = {1, 2, 3};
  }
  {
    using box_type = box<vec_type, vec_type>;
    BOOST_CHECK_EQUAL(elem<0>(min(box_type(vec_type({1, 2, 3}), vec_type({4, 5, 6})))), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(box_type(vec_type({1, 2, 3}), vec_type({4, 5, 6})))), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(box_type(vec_type({1, 2, 3}), vec_type({4, 5, 6})))), 3);
  }
}

BOOST_AUTO_TEST_CASE(min_ref_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::min;
  {
    vec_type array = {1, 2, 3};
    box<vec_type&, vec_type> b = {array, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
    array = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 9);
  }
  {
    vec_type const array = {1, 2, 3};
    box<vec_type const&, vec_type> b = {array, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(min(b)), 1);
    BOOST_CHECK_EQUAL(elem<1>(min(b)), 2);
    BOOST_CHECK_EQUAL(elem<2>(min(b)), 3);
    // Must not compile.
    // min(b) = {7, 8, 9};
  }
}
