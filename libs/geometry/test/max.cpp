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
#include <particle/geometry/max.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(max_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::max;
  {
    box<vec_type, vec_type> b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
    max(b) = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 9);
  }
  {
    box<vec_type, vec_type> const b = {{1, 2, 3}, {4, 5, 6}};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
  }
}

BOOST_AUTO_TEST_CASE(max_ref_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::max;
  {
    vec_type array = {4, 5, 6};
    box<vec_type, vec_type&> b = {{1, 2, 3}, array};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
    array = {7, 8, 9};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 7);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 8);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 9);
  }
  {
    vec_type const array = {4, 5, 6};
    box<vec_type, vec_type const&> b = {{1, 2, 3}, array};
    BOOST_CHECK_EQUAL(elem<0>(max(b)), 4);
    BOOST_CHECK_EQUAL(elem<1>(max(b)), 5);
    BOOST_CHECK_EQUAL(elem<2>(max(b)), 6);
    // Must not compile.
    // max(b) = {7, 8, 9};
  }
}
