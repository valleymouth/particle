#pragma once

// Boost headers
#include <boost/type_traits.hpp>

namespace particle
{
  namespace geometry
  {
    namespace traits
    {
      template <class>
      struct point_type;
    }

    template <class T>
    struct point_type
      : traits::point_type<typename boost::remove_const<T>::type>
    {};
  } // namespace geometry
} // namespace particle
