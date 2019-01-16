#pragma once

// Particle headers
#include "fold.hpp"
#include "transform.hpp"

namespace particle
{
namespace geometry
{
  template <typename L, typename R>
  PARTICLE_INLINE_FUNCTION
  auto distance_square(L&& lhs, R&& rhs)
  {
    return fold(
      transform(
        std::forward<L>(lhs)
        , std::forward<R>(rhs)
        , [](auto lhs, auto rhs) { auto d = lhs - rhs; return d * d; })
      , 0
      , [](auto s, auto x) { return s + x; });
  }

  template <typename L, typename R>
  PARTICLE_INLINE_FUNCTION
  auto distance(L&& lhs, R&& rhs)
  {
#ifndef __CUDACC__
    using std::sqrt;
#endif
    return sqrt(distance_square(std::forward<L>(lhs), std::forward<R>(rhs)));
  }
} // namespace geometry
} // namespace particle
