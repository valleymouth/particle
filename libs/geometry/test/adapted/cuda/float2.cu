// Boost test headers
#pragma push
#pragma diag_suppress = partial_override
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>
#pragma pop

// Particle headers
#include <particle/geometry/adapted/cuda/float2.hpp>
#include <particle/geometry/elem.hpp>

BOOST_AUTO_TEST_CASE(dim_test)
{
  using particle::geometry::traits::dim;

  constexpr float d = dim<float2>::value;
  BOOST_CHECK_EQUAL(d, 2);
}

BOOST_AUTO_TEST_CASE(elem_test)
{
  using particle::geometry::elem;

  using vec_type = float2;
  
  vec_type array = {1.0f, 2.0f};

  const float e = 1e-12f;
  BOOST_CHECK_CLOSE(elem<0>(array), 1.0f, e);
  BOOST_CHECK_CLOSE(elem<1>(array), 2.0f, e);
}
