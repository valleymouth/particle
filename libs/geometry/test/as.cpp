// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/as.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/intersect.hpp>
#include <particle/geometry/operators/add.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(as_vec_test)
{
  using particle::geometry::as;
  using particle::geometry::elem;
  using particle::geometry::operators::operator+;
 
  vec_type v0 = {1, 2, 3};
  vec_type v1 = {4, 5, 6};
  vec_type v2 = as<vec_type>(v0 + v1);
  BOOST_CHECK_EQUAL(elem<0>(v2), 5);
  BOOST_CHECK_EQUAL(elem<1>(v2), 7);
  BOOST_CHECK_EQUAL(elem<2>(v2), 9);

  vec_type v3 = as<vec_type>(vec_type({1, 2, 3}));
  BOOST_CHECK_EQUAL(elem<0>(v3), 1);
  BOOST_CHECK_EQUAL(elem<1>(v3), 2);
  BOOST_CHECK_EQUAL(elem<2>(v3), 3);
}

BOOST_AUTO_TEST_CASE(as_box_test)
{
  using particle::geometry::as;
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::intersect;

  box<vec_type, vec_type> b0 = {{-2, -3, -4}, {2, 3, 4}};
  box<vec_type, vec_type> b1 = {{-1, 0, -5}, {3, 5, 5}};
  box<vec_type, vec_type> b2 = as<box<vec_type, vec_type>>(intersect(b0, b1));
  BOOST_CHECK_EQUAL(elem<0>(min(b2)), -1);
  BOOST_CHECK_EQUAL(elem<1>(min(b2)), 0);
  BOOST_CHECK_EQUAL(elem<2>(min(b2)), -4);
  BOOST_CHECK_EQUAL(elem<0>(max(b2)), 2);
  BOOST_CHECK_EQUAL(elem<1>(max(b2)), 3);
  BOOST_CHECK_EQUAL(elem<2>(max(b2)), 4);
}
