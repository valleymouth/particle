#pragma once

// Local headers
#include "equal.hpp"
//#include "zero.hpp"

// Particle headers
#include "../config.hpp"

// Boost headers
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace particle
{
  namespace geometry
  {
    template <class Point>
    struct aabb
    {
      typedef Point point_type;

      Point min;
      Point max;

      // PARTICLE_INLINE_FUNCTION
      // aabb(): lower(zero<Point>()), upper(zero<Point>()) {}

      // PARTICLE_INLINE_FUNCTION
      // aabb(const Point &l, const Point &u): min(l), max(u) {}

      bool operator==(const aabb &bb) const
      {
	if (equal(min, bb.min) && equal(max, bb.max))
	  return true;
	return false;
      }

      bool operator!=(const aabb &bb) const
      {
	return !((*this) == bb);
      }
    };

    namespace traits
    {
      template <class>
      struct tag;

      template <class Point>
      struct tag<aabb<Point> >
	: boost::mpl::identity<tags::aabb_tag>
      {};

      template <class, class>
      struct min;
    
      template <class Point, class AABB>
      struct min<aabb<Point>, AABB>
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<AABB>
	  , const typename AABB::point_type &
	  , typename AABB::point_type &
	  >::type type;
      
	PARTICLE_INLINE_FUNCTION
	static type call(AABB &bb)
	{
	  return bb.min;
	}
      };

      template <class, class>
      struct max;

      template <class Point, class AABB>
      struct max<aabb<Point>, AABB>
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<AABB>
	  , const typename AABB::point_type &
	  , typename AABB::point_type &
	  >::type type;
      
	PARTICLE_INLINE_FUNCTION
	static type call(AABB &bb)
	{
	  return bb.max;
	}
      };

      template <class>
      struct point_type;

      template <class Point>
      struct point_type<aabb<Point>>
        : boost::mpl::identity<Point>
      {};
    } // namespace traits
  } // namespace geometry
} // namespace particle
