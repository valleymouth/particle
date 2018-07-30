#pragma once

// Local headers
#include "tag.hpp"

namespace particle
{
  namespace geometry
  {
    template <class T>
    struct value_type
      : traits::value_type<typename traits::tag<T>::type>
    {};
  } // namespace geometry
} // namespace particle
