#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"

// Boost headers
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class Box, class Point, std::size_t N>
      struct contains_impl
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const Box &box, const Point &p)
	{
          using boost::fusion::at_c;
	  return at_c<N>(min(box)) <= at_c<N>(p)
	    && at_c<N>(max(box)) > at_c<N>(p)
	    && contains_impl<Box, Point, N - 1>::call(box, p);
	}
      };

      template <class Box, class Point>
      struct contains_impl<Box, Point, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const Box &box, const Point &p)
	{
          using boost::fusion::at_c;
	  return at_c<0>(min(box)) <= at_c<0>(p)
	    && at_c<0>(max(box)) > at_c<0>(p);
	}
      };
    }

    template <class Box, class Point>
    PARTICLE_INLINE_FUNCTION
    bool contains(const Box &box, const Point &p)
    {
      using boost::fusion::result_of::size;
      return detail::contains_impl<
	Box
	, Point
	, size<typename Box::min_type>::value - 1>::call(box, p);
    }
  }
}
