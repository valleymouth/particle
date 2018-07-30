#pragma once

// Local headers
#include "lower.hpp"
#include "minus.hpp"
#include "upper.hpp"

// Particle headers
#include "../config.hpp"

namespace particle
{
  namespace geometry
  {
    template <class AABB>
    PARTICLE_INLINE_FUNCTION
    auto size(const AABB &aabb) -> decltype(minus(upper(aabb), lower(aabb)))
    {
      return minus(upper(aabb), lower(aabb));
    }
  }
}
