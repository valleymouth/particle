#pragma once

// Std headers
#include <type_traits>

namespace particle
{
namespace geometry
{
  namespace traits
  {
    template <typename, typename Enable = void>
    struct is_vector;

    template <typename T>
    struct is_vector<T, typename std::enable_if<std::is_arithmetic<T>::value>::type>
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
