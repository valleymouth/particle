#pragma once

// Particle headers
#include "../config.hpp"

namespace particle
{
  namespace geometry
  {
    namespace traits
    {
      template <class>
      struct min;
    } // namespace traits

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::min<T>::type min(T& p)
    {
      return traits::min<T>::call(p);
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::min<T const>::type min(T const& p)
    {
      return traits::min<T const>::call(p);
    }
  } // namespace geometry
} // namespace particle
