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
      struct max;
    } // namespace traits

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::max<T>::type max(T& p)
    {
      return traits::max<T>::call(p);
    }

    template <class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::max<T const>::type max(T const& p)
    {
      return traits::max<T const>::call(p);
    }
  } // namespace geometry
} // namespace particle
