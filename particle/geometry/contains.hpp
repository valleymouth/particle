#pragma once

// Local headers
#include "dimension.hpp"
#include "max.hpp"
#include "min.hpp"

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
	  return elem<N>(min(aabb)) <= elem<N>(p)
	    && elem<N>(max(aabb)) > elem<N>(p)
	    && contains_impl<AABB, Point, N - 1>::call(aabb, p);
	}
      };

      template <class AABB, class Point>
      struct contains_impl<AABB, Point, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb, const Point &p)
	{
	  return elem<0>(min(aabb)) <= elem<0>(p)
	    && elem<0>(max(aabb)) > elem<0>(p);
	}
      };
    }

    template <class AABB, class Point>
    PARTICLE_INLINE_FUNCTION
    bool contains(const AABB &aabb, const Point &p)
    {
      return detail::contains_impl<
	AABB
	, Point
	, traits::dimension<AABB>::type::value - 1>::call(aabb, p);
    }
  }
}
