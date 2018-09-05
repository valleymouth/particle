#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"
#include "point_type.hpp"
#include "tag.hpp"
#include "tags.hpp"

// Particle headers
#include "../config.hpp"

// Boost headers
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv_ref.hpp>

#include <type_traits>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class, class, class, class Enable = void>
      struct equal_impl;

      template <class T0, class T1, std::size_t N>
      struct equal_vector_impl
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T0 &lhs, const T1 &rhs)
	{
          using boost::fusion::at_c;
	  return at_c<N>(lhs) == at_c<N>(rhs)
	    && equal_vector_impl<T0, T1, N - 1>::call(lhs, rhs);
	}
      };

      template <class T0, class T1>
      struct equal_vector_impl<T0, T1, 0>
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T0 &lhs, const T1 &rhs)
	{
          using boost::fusion::at_c;
	  return at_c<0>(lhs) == at_c<0>(rhs);
	}
      };

      template <class T0, class T1>
      struct equal_impl<
        T0
        , T1
        , tags::vector_tag
        , typename std::enable_if<
            boost::fusion::result_of::size<T0>::value
            == boost::fusion::result_of::size<T1>::value
            >::type
        >
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T0 &lhs, const T1 &rhs)
	{
          using boost::fusion::result_of::size;
	  return equal_vector_impl<
	    T0
            , T1
	    , size<T0>::type::value - 1>::call(lhs, rhs);
	}
      };

      template <class T0, class T1>
      struct equal_impl<
        T0
        , T1
        , tags::aabb_tag
        , typename std::enable_if<
            boost::fusion::result_of::size<
              typename point_type<T0>::type>::value
            == boost::fusion::result_of::size<
              typename point_type<T1>::type>::value
            >::type
        >
      {
	PARTICLE_INLINE_FUNCTION
	static bool call(const T0 &lhs, const T1 &rhs)
	{
          using boost::remove_cv_ref;
	  return detail::equal_impl<
	    typename remove_cv_ref<decltype(min(lhs))>::type
            , typename remove_cv_ref<decltype(min(rhs))>::type
	    , tags::vector_tag>::call(min(lhs), min(rhs))
	    && detail::equal_impl<
	      typename remove_cv_ref<decltype(max(lhs))>::type
            , typename remove_cv_ref<decltype(max(rhs))>::type
	    , tags::vector_tag>::call(max(lhs), max(rhs));
	}
      };
    } // namespace detail
    
    template <
      class T0
      , class T1
      , typename std::enable_if<
          std::is_same<
            typename tag<T0>::type
            , typename tag<T1>::type
            >::value
          , int
          >::type = 0
      >
    PARTICLE_INLINE_FUNCTION
    bool equal(const T0 &lhs, const T1 &rhs)
    {
      return detail::equal_impl<T0, T1, typename tag<T0>::type>::call(lhs, rhs);
    }
  } // namespace geometry
} // namespace particle
