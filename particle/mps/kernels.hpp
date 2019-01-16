#pragma once

// mps headers
#include "../config.hpp"

namespace particle
{
namespace mps
{
  template <typename T>
  struct rational_kernel
  {
    T re;
    PARTICLE_INLINE_FUNCTION
    rational_kernel(T re): re(re) {}

    PARTICLE_INLINE_FUNCTION
    T operator()(T r) const
    {
      if (r < re)
        return re / r - 1;
      return 0;
    }
  };

  // see "Numerical Simulation of Three-Dimensional Free-Surface Flows with
  // Explicit Moving Particle Simulation Method"
  namespace yamada
  {
    template <typename T>
    struct kernel
    {
      T re;
      PARTICLE_INLINE_FUNCTION
      kernel(T re): re(re) {}

      PARTICLE_INLINE_FUNCTION
      T operator()(T r) const
      {
        if (r < re)
          return re / r + r / re - 2;
        return 0;
      }
    };

    template <typename T>
    struct gradient_kernel
    {
      T re;
      PARTICLE_INLINE_FUNCTION
      gradient_kernel(T re): re(re) {}

      PARTICLE_INLINE_FUNCTION
      T operator()(T r) const
      {
        if (r < re)
          return re / r - r / re;
        return 0;
      }
    };
  } // namespace yamada
} // namespace mps
} // namespace particle

