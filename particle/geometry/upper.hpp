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
      struct upper;
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::upper<T, T>::type upper(T &p)
    {
      return traits::upper<T, T>::call(p);
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::upper<T, const T>::type upper(const T &p)
    {
      return traits::upper<T, const T>::call(p);
    }
  } // namespace geometry
} // namespace particle
