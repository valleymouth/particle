#pragma once

namespace particle
{
namespace geometry
{
  namespace traits
  {
    template <typename>
    struct is_box
    {
      static constexpr int value = false;
    };

    template <typename T>
    struct is_box<T const>: is_box<T> {};
    template <typename T>
    struct is_box<T&>: is_box<T> {};
    template <typename T>
    struct is_box<T&&>: is_box<T> {};
  } // namespace traits
} // namespace geometry
} // namespace particle
