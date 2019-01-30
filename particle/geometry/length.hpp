#pragma once

// Particle headers
#include "fold.hpp"
#include "transform.hpp"

namespace particle
{
namespace geometry
{
  template <typename T>
  PARTICLE_INLINE_FUNCTION
  auto length_square(T&& x)
  {
    return fold(
      transform(
        std::forward<T>(x)
        , [](auto x) { return x * x; })
      , 0
      , [](auto s, auto x) { return s + x; });
  }

  template <typename T>
  PARTICLE_INLINE_FUNCTION
  auto length(T&& x)
  {
#ifndef __CUDACC__
    using std::sqrt;
#endif
    return sqrt(length_square(std::forward<T>(x)));
  }
} // namespace geometry
} // namespace particle
