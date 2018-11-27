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
  auto intersect(T0&& box0, T1&& box1)
  {
    return make_box(
      transform(
        min(std::forward<T0>(box0))
        , min(std::forward<T1>(box1))
        , [](auto x0, auto x1) { return std::max(x0, x1); })
      , transform(
        max(std::forward<T0>(box0))
        , max(std::forward<T1>(box1))
        , [](auto x0, auto x1) { return std::min(x0, x1); }));
  }
} // namespace geometry
} // namespace particle
