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
    struct dim;

    template <typename T>
    struct dim<
      T
      , typename std::enable_if<
          std::is_arithmetic<T>::value
          && !std::is_const<T>::value
          && !std::is_reference<T>::value>::type>
    {
      static constexpr int value = 1;
    };

    template <typename T>
    struct dim<T const>: dim<T> {};
    template <typename T>
    struct dim<T&>: dim<T> {};
    template <typename T>
    struct dim<T&&>: dim<T> {};
  } // namespace traits
} // namespace geometry
} // namespace particle
