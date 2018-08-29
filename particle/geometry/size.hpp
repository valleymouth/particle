#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"
#include "minus.hpp"

// Particle headers
#include "../config.hpp"

namespace particle
{
  namespace geometry
  {
    template <class AABB>
    PARTICLE_INLINE_FUNCTION
    auto size(const AABB &aabb) -> decltype(minus(max(aabb), min(aabb)))
    {
      return minus(max(aabb), min(aabb));
    }
  }
}
