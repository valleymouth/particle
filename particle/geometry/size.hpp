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
    template <class Box>
    PARTICLE_INLINE_FUNCTION
    auto size(Box const& box) -> decltype(minus(max(box), min(box)))
    {
      return minus(max(box), min(box));
    }
  } // namespace geometry
} // namespace particle
