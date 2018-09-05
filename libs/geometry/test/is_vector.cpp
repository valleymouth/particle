// Boost test headers
#define BOOST_TEST_MODULE geometry
#include <boost/test/included/unit_test.hpp>

// Particle headers
#include <particle/geometry/is_vector.hpp>

// Boost headers
#include <boost/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>

struct triple
{
  typedef int result_type;

  int operator()(int t) const
  {
    return 3 * t;
  }
};

BOOST_AUTO_TEST_CASE(is_vector_test)
{
  using particle::geometry::traits::is_vector;
  using boost::array;
  using boost::fusion::result_of::transform;
  
  BOOST_CHECK_EQUAL((is_vector<array<double, 3>>::value), true);
  BOOST_CHECK_EQUAL(is_vector<int>::value, false);
  BOOST_CHECK_EQUAL(
    (is_vector<transform<array<int, 3>, triple>::type>::value)
    , true);
}
