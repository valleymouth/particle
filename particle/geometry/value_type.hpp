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
    struct value_type;

    template <typename T>
    struct value_type<T, typename std::enable_if<std::is_arithmetic<T>::value>::type>
    {
      using type = T;
    };

    template <typename T>
    struct value_type<T const>: value_type<T> {};
    template <typename T>
    struct value_type<T&>: value_type<T> {};
    template <typename T>
    struct value_type<T&&>: value_type<T> {};
  } // namespace traits
} // namespace geometry
} // namespace particle
