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
      struct max;
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::max<T, T>::type max(T &p)
    {
      return traits::max<T, T>::call(p);
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::max<T, const T>::type max(const T &p)
    {
      return traits::max<T, const T>::call(p);
    }
  } // namespace geometry
} // namespace particle
