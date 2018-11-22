#pragma once

// Local headers
#include "fold.hpp"
#include "max.hpp"
#include "min.hpp"
#include "transform.hpp"

namespace particle
{
namespace geometry
{
  template <typename Box, typename T>
  PARTICLE_INLINE_FUNCTION
  bool contains(Box const& b, T const& x)
  {
    return fold(
      transform(
        transform(
          min(b)
          , x
          , [](auto min, auto x) { return min <= x; })
        , transform(
          max(b)
          , x
          , [](auto max, auto x) { return max > x; })
        , [](auto x0, auto x1) { return x0 && x1; })
      , true
      , [](auto s, auto x) { return s && x; });
  }
} // namespace geometry
} // namespace particle
