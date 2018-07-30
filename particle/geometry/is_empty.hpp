#pragma once

// Local headers
#include "dimension.hpp"
#include "lower.hpp"
#include "upper.hpp"

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
	  return elem<N>(lower(aabb)) >= elem<N>(upper(aabb))
	    || is_empty_impl<AABB, N - 1>::call(aabb);
	}
      };

      template <class AABB>
      struct is_empty_impl<AABB, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const AABB &aabb)
	{
	  return elem<0>(lower(aabb)) >= elem<0>(upper(aabb));
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
