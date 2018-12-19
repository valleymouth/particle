#pragma once

// Particle headers
#include "../config.hpp"
#include "transform.hpp"

namespace particle
{
namespace geometry
{
  template <typename T, typename U>
  PARTICLE_INLINE_FUNCTION
  auto cast(U&& x)
  {
    return transform(std::forward<U>(x), [](auto x) { return static_cast<T>(x); });
  }
} // namespace geometry
} // namespace particle
