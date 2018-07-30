// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/adapted/std_array.hpp>
#include <particle/geometry/aabb.hpp>
#include <particle/geometry/elem.hpp>
#include <particle/geometry/is_empty.hpp>
#include <particle/geometry/is_in.hpp>
#include <particle/geometry/lower.hpp>
#include <particle/geometry/minus.hpp>
#include <particle/geometry/plus.hpp>
#include <particle/geometry/size.hpp>
#include <particle/geometry/upper.hpp>

// Std headers
#include <array>

BOOST_AUTO_TEST_CASE(elem_test)
{
  using particle::geometry::elem;
  std::array<double, 3> array = {1.0, 2.0, 3.0};
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(array), 1.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(array), 2.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(array), 3.0, tol);
}

BOOST_AUTO_TEST_CASE(elem_ref_test)
{
  using particle::geometry::elem;
  std::array<double, 3> array = {1.0, 2.0, 3.0};
  elem<0>(array) = 4.0;
  elem<1>(array) = 5.0;
  elem<2>(array) = 6.0;
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(array), 4.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(array), 5.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(array), 6.0, tol);
}

BOOST_AUTO_TEST_CASE(plus_test)
{
  using particle::geometry::elem;
  using particle::geometry::plus;

  std::array<double, 3> array0 = {1.0, 2.0, 3.0};
  std::array<double, 3> array1 = {4.0, 5.0, 6.0};
  std::array<double, 3> array3 = plus(array0, array1);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(array3), 5.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(array3), 7.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(array3), 9.0, tol);
}

BOOST_AUTO_TEST_CASE(minus_test)
{
  using particle::geometry::elem;
  using particle::geometry::minus;

  std::array<double, 3> array0 = {1.0, 2.0, 3.0};
  std::array<double, 3> array1 = {4.0, 5.0, 6.0};
  std::array<double, 3> array3 = minus(array0, array1);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(array3), -3.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(array3), -3.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(array3), -3.0, tol);
}

BOOST_AUTO_TEST_CASE(lower_test)
{
  using particle::geometry::aabb;
  using particle::geometry::elem;
  using particle::geometry::lower;
  
  aabb<std::array<double, 3>> box(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  std::array<double, 3> l = lower(box);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(l), -2.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(l), 3.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(l), -5.0, tol);
}

BOOST_AUTO_TEST_CASE(upper_test)
{
  using particle::geometry::aabb;
  using particle::geometry::elem;
  using particle::geometry::upper;
  
  aabb<std::array<double, 3>> box(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  std::array<double, 3> u = upper(box);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(u), 1.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(u), 5.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(u), 1.0, tol);
}

BOOST_AUTO_TEST_CASE(is_empty_test)
{
  using particle::geometry::aabb;
  using particle::geometry::is_empty;

  aabb<std::array<double, 3>> box0(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  BOOST_CHECK_EQUAL(is_empty(box0), false);

  aabb<std::array<double, 3>> box1(
    {-2.0, 3.0, -5.0}
    , {1.0, 2.0, 1.0});
  BOOST_CHECK_EQUAL(is_empty(box1), true);
}

BOOST_AUTO_TEST_CASE(is_in_test)
{
  using particle::geometry::aabb;
  using particle::geometry::is_in;

  aabb<std::array<double, 3>> box(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  std::array<double, 3> p0 = {-1.0, 4.0, -2.0};
  BOOST_CHECK_EQUAL(is_in(box, p0), true);
  std::array<double, 3> p1 = {-1.0, 1.0, -2.0};
  BOOST_CHECK_EQUAL(is_in(box, p1), false);
}

BOOST_AUTO_TEST_CASE(size_test)
{
  using particle::geometry::aabb;
  using particle::geometry::elem;
  using particle::geometry::size;

  aabb<std::array<double, 3>> box(
    {-2.0, 3.0, -5.0}
    , {1.0, 5.0, 1.0});
  std::array<double, 3> s = size(box);
  const double tol = 1e-20;
  BOOST_CHECK_CLOSE(elem<0>(s), 3.0, tol);
  BOOST_CHECK_CLOSE(elem<1>(s), 2.0, tol);
  BOOST_CHECK_CLOSE(elem<2>(s), 6.0, tol);
}

BOOST_AUTO_TEST_CASE(equal_vector_test)
{
  using particle::geometry::equal;

  std::array<int, 3> v0 = {1, 2, 3};
  std::array<int, 3> v1 = {1, 2, 3};
  std::array<int, 3> v2 = {1, 1, 3};
  BOOST_CHECK_EQUAL(equal(v0, v1), true);
  BOOST_CHECK_EQUAL(equal(v1, v2), false);
}

BOOST_AUTO_TEST_CASE(equal_aabb_test)
{
  using particle::geometry::aabb;
  using particle::geometry::equal;

  aabb<std::array<int, 3>> box0(
    {-2, 3, -5}
    , {1, 5, 1});
  aabb<std::array<int, 3>> box1(
    {-2, 3, -5}
    , {1, 5, 1});
  aabb<std::array<int, 3>> box2(
    {-2, 3, -5}
    , {1, 4, 1});
  BOOST_CHECK_EQUAL(equal(box0, box1), true);
  BOOST_CHECK_EQUAL(equal(box1, box2), false);
}
