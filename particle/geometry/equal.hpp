#pragma once

// Local headers
#include "elem.hpp"
#include "max.hpp"
#include "min.hpp"

// Particle headers
#include "../config.hpp"

// Boost headers
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv_ref.hpp>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class, class>
      struct equal_impl;

      template <class T, std::size_t N>
      struct equal_vector_impl_recursive
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T &lhs, const T &rhs)
	{
	  return elem<N>(lhs) == elem<N>(rhs)
	    && equal_vector_impl_recursive<T, N - 1>::call(lhs, rhs);
	}
      };

      template <class T>
      struct equal_vector_impl_recursive<T, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T &lhs, const T &rhs)
	{
	  return elem<0>(lhs) == elem<0>(rhs);
	}
      };

      template <class T>
      struct equal_impl<T, tags::vector_tag>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T &lhs, const T &rhs)
	{
	  return equal_vector_impl_recursive<
	    T
	    , traits::dimension<T>::type::value - 1>::call(lhs, rhs);
	}
      };

      template <class T>
      struct equal_impl<T, tags::aabb_tag>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T &lhs, const T &rhs)
	{
	  return detail::equal_impl<
	    typename boost::remove_cv_ref<
	      decltype(min(lhs))>::type
	    , tags::vector_tag>::call(min(lhs), min(rhs))
	    && detail::equal_impl<
	      typename boost::remove_cv_ref<
		decltype(max(lhs))>::type
	    , tags::vector_tag>::call(max(lhs), max(rhs));
	}
      };
    } // namespace detail
    
    template <class T>
    PARTICLE_INLINE_FUNCTION
    bool equal(const T &lhs, const T &rhs)
    {
      return detail::equal_impl<T, typename tag<T>::type>::call(lhs, rhs);
    }
  } // namespace geometry
} // namespace particle
