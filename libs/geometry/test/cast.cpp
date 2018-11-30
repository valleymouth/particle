// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/float3.hpp>
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/cast.hpp>

#ifdef __CUDACC__
using float_vec_type = float3;
using int_vec_type = int3;
#else
using float_vec_type = std::array<float, 3>;
using int_vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(cast_test)
{
  using particle::geometry::cast;
  using particle::geometry::elem;

  float_vec_type array0 = {1.2, 2.4, 3.6};
  auto array1 = cast<int>(array0);
  BOOST_CHECK_EQUAL(elem<0>(array1), 1);
  BOOST_CHECK_EQUAL(elem<1>(array1), 2);
  BOOST_CHECK_EQUAL(elem<2>(array1), 3);
}
