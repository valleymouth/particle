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
    return box<
      typename std::conditional<
        std::is_rvalue_reference<Min>::value
        , typename std::remove_reference<Min>::type
        , Min>::type
      , typename std::conditional<
        std::is_rvalue_reference<Max>::value
          , typename std::remove_reference<Max>::type
          , Max>::type
      >(min, max);
  }
} // namespace geometry
} // namespace particle
