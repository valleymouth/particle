#pragma once

// Particle headers
#include "transform.hpp"

namespace particle
{
namespace geometry
{
  template <typename L, typename R>
  PARTICLE_INLINE_FUNCTION
  auto div(L&& lhs, R&& rhs)
  {
    return transform(
      std::forward<L>(lhs)
      , std::forward<R>(rhs)
      , [](auto lhs, auto rhs) { return lhs / rhs; } );
  }
} // namespace geometry
} // namespace particle
