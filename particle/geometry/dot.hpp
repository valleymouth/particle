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
  auto dot(L&& lhs, R&& rhs)
  {
    return fold(
      transform(
        std::forward<L>(lhs)
        , std::forward<R>(rhs)
        , [](auto lhs, auto rhs) { return lhs * rhs; })
      , 0
      , [](auto s, auto x) { return s + x; });
  }
} // namespace geometry
} // namespace particle
