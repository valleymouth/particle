#pragma once

// Particle headers
#include "elem.hpp"
#include "is_box.hpp"
#include "is_vector.hpp"

namespace particle
{
namespace geometry
{
  namespace detail
  {
    template <int I, int N>
    struct as_vec_impl_
    {
      template <typename T, typename R>
      PARTICLE_STATIC_FUNCTION
      auto apply(T&& x, R& r)
      {
        elem<I>(r) = elem<I>(x);
        as_vec_impl_<I + 1, N>::apply(std::forward<T>(x), r);
      }
    };

    template <int N>
    struct as_vec_impl_<N, N>
    {
      template <typename T, typename R>
      PARTICLE_STATIC_FUNCTION
      auto apply(T&& x, R& r)
      {
        elem<N>(r) = elem<N>(x);
      }
    };
    
    template <typename R, typename T>
    PARTICLE_INLINE_FUNCTION
    R as_vec_impl(T&& x)
    {
      R result;
      detail::as_vec_impl_<0, traits::dim<T>::value - 1>::apply(std::forward<T>(x), result);
      return result;
    }
    
    template <typename R, typename T>
    PARTICLE_INLINE_FUNCTION
    R as_box_impl(T&& x)
    {
      R result;
      detail::as_vec_impl_<0, traits::dim<T>::value - 1>::apply(min(x), min(result));
      detail::as_vec_impl_<0, traits::dim<T>::value - 1>::apply(max(x), max(result));
      return result;
    }
  } // namespace detail

  template <
    typename R
    , typename T
    , typename std::enable_if<
        traits::is_vector<T>::value
        , int>::type = 0>
  PARTICLE_INLINE_FUNCTION
  R as(T&& x)
  {
    return detail::as_vec_impl<R>(std::forward<T>(x));
  }
  
  template <
    typename R
    , typename T
    , typename std::enable_if<
        traits::is_box<T>::value
        , int>::type = 0>
  PARTICLE_INLINE_FUNCTION
  R as(T&& x)
  {
    return detail::as_box_impl<R>(std::forward<T>(x));
  }
} // namespace geometry
} // namespace particle
