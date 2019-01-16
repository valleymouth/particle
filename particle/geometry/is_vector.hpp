#pragma once

// Std headers
#include <type_traits>

namespace particle
{
namespace geometry
{
  namespace traits
  {
    template <typename>
    struct is_vector
    {
      static constexpr bool value = false;
    };

    template <typename T>
    struct is_vector<T const>: is_vector<T> {};
    template <typename T>
    struct is_vector<T&>: is_vector<T> {};
    template <typename T>
    struct is_vector<T&&>: is_vector<T> {};
  } // namespace traits
} // namespace geometry
} // namespace particle
