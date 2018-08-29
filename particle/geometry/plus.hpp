#pragma once

// Local headers
#include "dimension.hpp"
#include "elem.hpp"

// Particle headers
#include "../config.hpp"

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class T, std::size_t N>
      struct plus_impl_recursive
      {
	PARTICLE_INLINE_FUNCTION
	static void call(const T &lhs, const T &rhs, T &result)
	{
	  elem<N>(result) = elem<N>(lhs) + elem<N>(rhs);
	  plus_impl_recursive<T, N - 1>::call(lhs, rhs, result);
	}
      };

      template <class T>
      struct plus_impl_recursive<T, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static void call(const T &lhs, const T &rhs, T &result)
	{
	  elem<0>(result) = elem<0>(lhs) + elem<0>(rhs);
	}
      };

      template <class T>
      struct plus_impl
      {
	PARTICLE_INLINE_FUNCTION
	static T call(const T &lhs, const T &rhs)
	{
	  T result;
	  plus_impl_recursive<
	    T
	    , dimension<T>::type::value - 1
	    >::call(lhs, rhs, result);
	  return result;
	}
      };
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    T plus(const T &lhs, const T &rhs)
    {
      return detail::plus_impl<T>::call(lhs, rhs);
    }
  } // namespace geometry
} // namespace particle
