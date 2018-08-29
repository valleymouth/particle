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
      template <class AABB, std::size_t N>
      struct is_empty_impl
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb)
	{
	  return elem<N>(min(aabb)) >= elem<N>(max(aabb))
	    || is_empty_impl<AABB, N - 1>::call(aabb);
	}
      };

      template <class AABB>
      struct is_empty_impl<AABB, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb)
	{
	  return elem<0>(min(aabb)) >= elem<0>(max(aabb));
	}
      };
    } // namespace detail

    template <class AABB>
    PARTICLE_INLINE_FUNCTION
    bool is_empty(const AABB &aabb)
    {
      return detail::is_empty_impl<
	AABB, traits::dimension<AABB>::type::value - 1>::call(aabb);
    }
  } // namespace geometry
} // namespace particle
