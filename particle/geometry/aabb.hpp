#pragma once

// Local headers
#include "dimension.hpp"
#include "elem.hpp"
#include "equal.hpp"
#include "lower.hpp"
//#include "upper.hpp"
//#include "zero.hpp"

// Particle headers
#include "../config.hpp"

// Cuda headers
#include <thrust/functional.h>

// Boost headers
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

// Std headers
#include <algorithm>

namespace particle
{
  namespace geometry
  {
    template <class Point>
    struct aabb
    {
      typedef Point point_type;

      Point lower;
      Point upper;

      // PARTICLE_INLINE_FUNCTION
      // aabb(): lower(zero<Point>()), upper(zero<Point>()) {}

      PARTICLE_INLINE_FUNCTION
      aabb(const Point &l, const Point &u): lower(l), upper(u) {}

      bool operator==(const aabb &bb) const
      {
	if (equal(lower, bb.lower) && equal(upper, bb.upper))
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

      template <class>
      struct dimension;

      template <class Point>
      struct dimension<aabb<Point>>
	: traits::dimension<Point>
      {};

      template <class, class>
      struct lower;
    
      template <class Point, class AABB>
      struct lower<aabb<Point>, AABB>
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<AABB>
	  , const typename AABB::point_type &
	  , typename AABB::point_type &
	  >::type type;
      
	PARTICLE_INLINE_FUNCTION
	static type call(AABB &bb)
	{
	  return bb.lower;
	}
      };

      template <class, class>
      struct upper;

      template <class Point, class AABB>
      struct upper<aabb<Point>, AABB>
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<AABB>
	  , const typename AABB::point_type &
	  , typename AABB::point_type &
	  >::type type;
      
	PARTICLE_INLINE_FUNCTION
	static type call(AABB &bb)
	{
	  return bb.upper;
	}
      };
    } // namespace traits

    //   namespace detail
    //   {
    //     template <int>
    //     struct is_empty;

    //     template <>
    //     struct is_empty<2>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static bool call(const AABB &bb)
    //       {
    //         return at_c<0>(lower(bb)) >= at_c<0>(upper(bb))
    //           || at_c<1>(lower(bb)) >= at_c<1>(upper(bb));
    //       }
    //     };

    //     template <>
    //     struct is_empty<3>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static bool call(const AABB &bb)
    //       {
    //         return at_c<0>(lower(bb)) >= at_c<0>(upper(bb))
    //           || at_c<1>(lower(bb)) >= at_c<1>(upper(bb))
    //           || at_c<2>(lower(bb)) >= at_c<2>(upper(bb));
    //       }
    //     };
    //   } // namespace detail

    //   template <class AABB>
    //   PARTICLE_INLINE_FUNCTION
    //   inline bool is_empty(const AABB &bb)
    //   {
    //     return detail::is_empty<
    //       traits::dimension_of<AABB>::type::value
    //     >::call(bb);
    //   }

    //   namespace detail
    //   {
    //     template <int>
    //     struct in;

    //     template <>
    //     struct in<2>
    //     {
    //       template <class AABB, class Point>
    //       PARTICLE_INLINE_FUNCTION
    //       static bool call(const AABB &bb, const Point &p)
    //       {
    //         return at_c<0>(lower(bb)) <= at_c<0>(p)
    //           && at_c<0>(upper(bb)) > at_c<0>(p)
    //           && at_c<1>(lower(bb)) <= at_c<1>(p)
    //           && at_c<1>(upper(bb)) > at_c<1>(p);
    //       }
    //     };

    //     template <>
    //     struct in<3>
    //     {
    //       template <class AABB, class Point>
    //       PARTICLE_INLINE_FUNCTION
    //       static bool call(const AABB &bb, const Point &p)
    //       {
    //         return at_c<0>(lower(bb)) <= at_c<0>(p)
    //           && at_c<0>(upper(bb)) > at_c<0>(p)
    //           && at_c<1>(lower(bb)) <= at_c<1>(p)
    //           && at_c<1>(upper(bb)) > at_c<1>(p)
    //           && at_c<2>(lower(bb)) <= at_c<2>(p)
    //           && at_c<2>(upper(bb)) > at_c<2>(p);
    //       }
    //     };
    //   } // namespace detail

    //   template <class AABB, class Point>
    //   PARTICLE_INLINE_FUNCTION
    //   inline bool in(const AABB &bb, const Point &p)
    //   {
    //     return detail::in<
    //       traits::dimension_of<AABB>::type::value
    //     >::call(bb, p);
    //   }

    //   namespace detail
    //   {
    //     template <int>
    //     struct size;

    //     template <>
    //     struct size<2>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static typename AABB::point_type call(const AABB &bb)
    //       {
    //         typename AABB::point_type ret;
    //         at_c<0>(ret) = at_c<0>(upper(bb)) - at_c<0>(lower(bb));
    //         at_c<1>(ret) = at_c<1>(upper(bb)) - at_c<1>(lower(bb));
    //         return ret;
    //       }
    //     };

    //     template <>
    //     struct size<3>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static typename AABB::point_type call(const AABB &bb)
    //       {
    //         typename AABB::point_type ret;
    //         at_c<0>(ret) = at_c<0>(upper(bb)) - at_c<0>(lower(bb));
    //         at_c<1>(ret) = at_c<1>(upper(bb)) - at_c<1>(lower(bb));
    //         at_c<2>(ret) = at_c<2>(upper(bb)) - at_c<2>(lower(bb));
    //         return ret;
    //       }
    //     };
    //   } // namespace detail

    //   template <class AABB>
    //   PARTICLE_INLINE_FUNCTION
    //   inline typename AABB::point_type size(const AABB &bb)
    //   {
    //     return detail::size<traits::dimension_of<AABB>::type::value>::call(bb);
    //   }

    //   namespace detail
    //   {
    //     template <int>
    //     struct intersect;

    //     template <>
    //     struct intersect<2>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static AABB call(const AABB &bb0, const AABB &bb1)
    //       {
    // #ifndef __CUDACC__
    //         using std::min;
    //         using std::max;
    // #endif

    //         AABB ret;
    //         at_c<0>(lower(ret)) = max(at_c<0>(lower(bb0)), at_c<0>(lower(bb1)));
    //         at_c<1>(lower(ret)) = max(at_c<1>(lower(bb0)), at_c<1>(lower(bb1)));
    //         at_c<0>(upper(ret)) = min(at_c<0>(upper(bb0)), at_c<0>(upper(bb1)));
    //         at_c<1>(upper(ret)) = min(at_c<1>(upper(bb0)), at_c<1>(upper(bb1)));
    //         return ret;
    //       }
    //     };

    //     template <>
    //     struct intersect<3>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static AABB call(const AABB &bb0, const AABB &bb1)
    //       {
    // #ifndef __CUDACC__
    //         using std::min;
    //         using std::max;
    // #endif

    //         AABB ret;
    //         at_c<0>(lower(ret)) = max(at_c<0>(lower(bb0)), at_c<0>(lower(bb1)));
    //         at_c<1>(lower(ret)) = max(at_c<1>(lower(bb0)), at_c<1>(lower(bb1)));
    //         at_c<2>(lower(ret)) = max(at_c<2>(lower(bb0)), at_c<2>(lower(bb1)));
    //         at_c<0>(upper(ret)) = min(at_c<0>(upper(bb0)), at_c<0>(upper(bb1)));
    //         at_c<1>(upper(ret)) = min(at_c<1>(upper(bb0)), at_c<1>(upper(bb1)));
    //         at_c<2>(upper(ret)) = min(at_c<2>(upper(bb0)), at_c<2>(upper(bb1)));
    //         return ret;
    //       }
    //     };
    //   } // namespace detail

    //   template <class AABB>
    //   PARTICLE_INLINE_FUNCTION
    //   inline AABB intersect(const AABB &bb0, const AABB &bb1)
    //   {
    //     return detail::intersect<
    //       traits::dimension_of<AABB>::type::value
    //     >::call(bb0, bb1);
    //   }

    //   namespace detail
    //   {
    //     template <int>
    //     struct extend;

    //     template <>
    //     struct extend<2>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static AABB call(const AABB &bb)
    //       {
    //         AABB ret = bb;
    //         at_c<0>(lower(ret)) -= 1;
    //         at_c<1>(lower(ret)) -= 1;
    //         at_c<0>(upper(ret)) += 1;
    //         at_c<1>(upper(ret)) += 1;
    //         return ret;
    //       }
    //     };

    //     template <>
    //     struct extend<3>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static AABB call(const AABB &bb)
    //       {
    //         AABB ret = bb;
    //         at_c<0>(lower(ret)) -= 1;
    //         at_c<1>(lower(ret)) -= 1;
    //         at_c<2>(lower(ret)) -= 1;
    //         at_c<0>(upper(ret)) += 1;
    //         at_c<1>(upper(ret)) += 1;
    //         at_c<2>(upper(ret)) += 1;
    //         return ret;
    //       }
    //     };
    //   } // namespace detail

    //   template <class AABB>
    //   PARTICLE_INLINE_FUNCTION
    //   inline AABB extend(const AABB &bb)
    //   {
    //     return detail::extend<
    //       traits::dimension_of<AABB>::type::value
    //     >::call(bb);
    //   }

    //   namespace detail
    //   {
    //     template <int>
    //     struct hull;

    //     template <>
    //     struct hull<2>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static AABB call(const AABB &bb0, const AABB &bb1)
    //       {
    // #ifndef __CUDACC__
    //         using std::min;
    //         using std::max;
    // #endif

    //         AABB ret;
    //         at_c<0>(lower(ret)) = min(at_c<0>(lower(bb0)), at_c<0>(lower(bb1)));
    //         at_c<1>(lower(ret)) = min(at_c<1>(lower(bb0)), at_c<1>(lower(bb1)));
    //         at_c<0>(upper(ret)) = max(at_c<0>(upper(bb0)), at_c<0>(upper(bb1)));
    //         at_c<1>(upper(ret)) = max(at_c<1>(upper(bb0)), at_c<1>(upper(bb1)));
    //         return ret;
    //       }
    //     };

    //     template <>
    //     struct hull<3>
    //     {
    //       template <class AABB>
    //       PARTICLE_INLINE_FUNCTION
    //       static AABB call(const AABB &bb0, const AABB &bb1)
    //       {
    // #ifndef __CUDACC__
    //         using std::min;
    //         using std::max;
    // #endif

    //         AABB ret;
    //         at_c<0>(lower(ret)) = min(at_c<0>(lower(bb0)), at_c<0>(lower(bb1)));
    //         at_c<1>(lower(ret)) = min(at_c<1>(lower(bb0)), at_c<1>(lower(bb1)));
    //         at_c<2>(lower(ret)) = min(at_c<2>(lower(bb0)), at_c<2>(lower(bb1)));
    //         at_c<0>(upper(ret)) = max(at_c<0>(upper(bb0)), at_c<0>(upper(bb1)));
    //         at_c<1>(upper(ret)) = max(at_c<1>(upper(bb0)), at_c<1>(upper(bb1)));
    //         at_c<2>(upper(ret)) = max(at_c<2>(upper(bb0)), at_c<2>(upper(bb1)));
    //         return ret;
    //       }
    //     };
    //   }

    //   template <class AABB>
    //   PARTICLE_INLINE_FUNCTION
    //   inline AABB hull(const AABB &bb0, const AABB &bb1)
    //   {
    //     return detail::hull<
    //       traits::dimension_of<AABB>::type::value
    //     >::call(bb0, bb1);
    //   }
  } // namespace geometry
} // namespace particle
