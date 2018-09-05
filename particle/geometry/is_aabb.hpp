#pragma once

// Local headers
#include "tag.hpp"
#include "tags.hpp"

// Std headers
#include <type_traits>

namespace particle
{
  namespace geometry
  {
    namespace traits
    {
      template <class T>
      struct is_aabb
        : std::is_same<
        tags::aabb_tag
        , typename tag<T>::type>
      {};
    } // namespace traits
  } // namespace geometry
} // namespace particle
