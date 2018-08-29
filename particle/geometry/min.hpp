#pragma once

// Particle headers
#include "../config.hpp"

namespace particle
{
  namespace geometry
  {
    namespace traits
    {
      template <class, class>
      struct min;
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::min<T, T>::type min(T &p)
    {
      return traits::min<T, T>::call(p);
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::min<T, const T>::type min(const T &p)
    {
      return traits::min<T, const T>::call(p);
    }
  } // namespace geometry
} // namespace particle