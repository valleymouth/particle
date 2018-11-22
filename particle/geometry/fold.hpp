#pragma once

// Particle headers
#include "dim.hpp"
#include "elem.hpp"

namespace particle
{
namespace geometry
{
  namespace detail
  {
    template <int I, int N>
    struct fold_impl_
    {
      template <typename T, typename F>
      PARTICLE_STATIC_FUNCTION
      auto apply(T&& x, F&& f)
      {
        return f(elem<I>(x), fold_impl_<I + 1, N>::apply(x, f));
      }
    };

    template <int N>
    struct fold_impl_<N, N>
    {
      template <typename T, typename F>
      PARTICLE_STATIC_FUNCTION
      auto apply(T&& x, F&&)
      {
        return elem<N>(x);
      }
    };

    template <typename T, typename S, typename F>
    PARTICLE_INLINE_FUNCTION
    auto fold_impl(T&& x, S&& s, F&& f)
    {
      return f(s, detail::fold_impl_<0, traits::dim<T>::value - 1>::apply(x, f));
    }
  }

  template <typename T, typename S, typename F>
  PARTICLE_INLINE_FUNCTION
  auto fold(T &&x, S&& s, F&& f)
  {
    return detail::fold_impl(x, s, f);
  }
} // namespace geometry
} // namespace particle
