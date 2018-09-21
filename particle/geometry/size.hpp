#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"
#include "sub.hpp"

// Particle headers
#include "../config.hpp"

namespace particle
{
  namespace geometry
  {
    template <class Box>
    PARTICLE_INLINE_FUNCTION
    auto size(Box const& box) -> decltype(sub(max(box), min(box)))
    {
      return sub(max(box), min(box));
    }
  } // namespace geometry
} // namespace particle
