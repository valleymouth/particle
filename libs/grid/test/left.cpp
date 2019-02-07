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
#include <particle/grid/left.hpp>

#ifdef __CUDACC__
using cell_type = int3;
#else
using cell_type = std::array<int, 3>;
#endif

BOOST_AUTO_TEST_CASE(left_test)
{
  using particle::geometry::box;
  using particle::sfc::left;

  box<cell_type, cell_type> b = {{-2, 3, -5}, {1, 5, 1}};
  cell_type cell0 = {-1, 4, -2};
  BOOST_CHECK_EQUAL(left(b, cell0), 22);
}
