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
      struct lower;
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::lower<T, T>::type lower(T &p)
    {
      return traits::lower<T, T>::call(p);
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::lower<T, const T>::type lower(const T &p)
    {
      return traits::lower<T, const T>::call(p);
    }
  } // namespace geometry
} // namespace particle
