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
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::min<T>::type min(T &p)
    {
      return traits::min<T>::call(p);
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::min<const T>::type min(const T &p)
    {
      return traits::min<const T>::call(p);
    }
  } // namespace geometry
} // namespace particle
