#pragma once

// local headers
#include "tag.hpp"

namespace particle
{
  namespace geometry
  {
    namespace traits
    {
      template <class>
      struct dimension;
    }
    
    template <class T>
    struct dimension
      : traits::dimension<typename boost::remove_const<T>::type>
    {};
  } // namespace geometry
} // namespace particle
