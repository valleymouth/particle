#pragma once

// Local headers
#include "box.hpp"

namespace particle
{
  namespace geometry
  {
    template <class T0, class T1>
    PARTICLE_INLINE_FUNCTION
    box<T0, T1> make_box(T0 const& p0, T1 const& p1)
    {
      return box<T0, T1>(p0, p1);
    }
  } // namespace geometry
} // namespace particle
