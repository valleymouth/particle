#pragma once

// Particle headers
#include "../config.hpp"
#include "make_box.hpp"
#include "max.hpp"
#include "min.hpp"
#include "transform.hpp"

namespace particle
{
namespace geometry
{
  template <typename T0, typename T1>
  PARTICLE_INLINE_FUNCTION
  auto intersect(T0 const& box0, T1 const& box1)
  {
    return make_box(
      transform(
        min(box0)
        , min(box1)
        , [](auto x0, auto x1) { return std::max(x0, x1); })
      , transform(
        max(box0)
        , max(box1)
        , [](auto x0, auto x1) { return std::min(x0, x1); }));
  }
} // namespace geometry
} // namespace particle
