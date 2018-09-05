#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"
#include "point_type.hpp"

// Boost headers
#include <boost/fusion/sequence/intrinsic/at_c.hpp>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class AABB, class Point, std::size_t N>
      struct contains_impl
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb, const Point &p)
	{
          using boost::fusion::at_c;
	  return at_c<N>(min(aabb)) <= at_c<N>(p)
	    && at_c<N>(max(aabb)) > at_c<N>(p)
	    && contains_impl<AABB, Point, N - 1>::call(aabb, p);
	}
      };

      template <class AABB, class Point>
      struct contains_impl<AABB, Point, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb, const Point &p)
	{
          using boost::fusion::at_c;
	  return at_c<0>(min(aabb)) <= at_c<0>(p)
	    && at_c<0>(max(aabb)) > at_c<0>(p);
	}
      };
    }

    template <class AABB, class Point>
    PARTICLE_INLINE_FUNCTION
    bool contains(const AABB &aabb, const Point &p)
    {
      using boost::fusion::result_of::size;
      return detail::contains_impl<
	AABB
	, Point
	, size<typename point_type<AABB>::type>::type::value - 1>::call(aabb, p);
    }
  }
}
