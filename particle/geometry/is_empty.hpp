#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"
#include "point_type.hpp"

// Boost headers
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class AABB, std::size_t N>
      struct is_empty_impl
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb)
	{
          using boost::fusion::at_c;
	  return at_c<N>(min(aabb)) >= at_c<N>(max(aabb))
	    || is_empty_impl<AABB, N - 1>::call(aabb);
	}
      };

      template <class AABB>
      struct is_empty_impl<AABB, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb)
	{
          using boost::fusion::at_c;
	  return at_c<0>(min(aabb)) >= at_c<0>(max(aabb));
	}
      };
    } // namespace detail

    template <class AABB>
    PARTICLE_INLINE_FUNCTION
    bool is_empty(const AABB &aabb)
    {
      return detail::is_empty_impl<
	AABB, boost::fusion::result_of::size<typename point_type<AABB>::type>::type::value - 1>::call(aabb);
    }
  } // namespace geometry
} // namespace particle
