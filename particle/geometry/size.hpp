#pragma once

// Particle headers
#include "max.hpp"
#include "min.hpp"
#include "sub.hpp"

namespace particle
{
namespace geometry
{
  template <class Box>
  PARTICLE_INLINE_FUNCTION
  decltype(auto) size(Box& box)
  {
    return sub(max(box), min(box));
  }
} // namespace geometry
} // namespace particle
