#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"

// Boost headers
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class Box, std::size_t N>
      struct is_empty_impl
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const Box &box)
	{
          using boost::fusion::at_c;
	  return at_c<N>(min(box)) >= at_c<N>(max(box))
	    || is_empty_impl<Box, N - 1>::call(box);
	}
      };

      template <class Box>
      struct is_empty_impl<Box, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const Box &box)
	{
          using boost::fusion::at_c;
	  return at_c<0>(min(box)) >= at_c<0>(max(box));
	}
      };
    } // namespace detail

    template <class Box>
    PARTICLE_INLINE_FUNCTION
    bool is_empty(const Box &box)
    {
      return detail::is_empty_impl<
	Box, boost::fusion::result_of::size<typename Box::min_type>::value - 1>::call(box);
    }
  } // namespace geometry
} // namespace particle
