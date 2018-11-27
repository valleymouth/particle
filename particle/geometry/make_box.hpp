#pragma once

// Particle headers
#include "box.hpp"

namespace particle
{
namespace geometry
{
  template <typename Min, typename Max>
  PARTICLE_INLINE_FUNCTION
  auto make_box(Min&& min, Max&& max)
  {
    return box<Min, Max>(min, max);
  }
} // namespace geometry
} // namespace particle
