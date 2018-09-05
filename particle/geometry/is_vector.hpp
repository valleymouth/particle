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
      struct is_vector
        : std::is_same<
        tags::vector_tag
        , typename tag<T>::type>
      {};
    } // namespace traits
  } // namespace geometry
} // namespace particle
