#pragma once

// Particle headers
#include "fold.hpp"
#include "max.hpp"
#include "min.hpp"
#include "transform.hpp"

namespace particle
{
namespace geometry
{
  template <typename Box>
  PARTICLE_INLINE_FUNCTION
  bool is_empty(Box&& b)
  {
    return fold(
      transform(
        min(b)
        , max(b)
        , [](auto min, auto max) { return min >= max; })
      , false
      , [](auto s, auto x) { return s || x; });
  }
} // namespace geometry
} // namespace particle
