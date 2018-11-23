// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#ifdef __CUDACC__
#include <particle/geometry/adapted/cuda/int3.hpp>
#else
#include <particle/geometry/adapted/std_array.hpp>
#endif
#include <particle/geometry/box.hpp>
#include <particle/geometry/size.hpp>

#ifdef __CUDACC__
using vec_type = int3;
#else
using vec_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(size_test)
{
  using particle::geometry::box;
  using particle::geometry::elem;
  using particle::geometry::size;

  box<vec_type, vec_type> b = {{-2, 3, -5}, {1, 5, 1}};

  auto s = size(b);

  BOOST_CHECK_EQUAL(elem<0>(s), 3);
  BOOST_CHECK_EQUAL(elem<1>(s), 2);
  BOOST_CHECK_EQUAL(elem<2>(s), 6);
}
