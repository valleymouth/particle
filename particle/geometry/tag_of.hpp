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
    struct tag_of;

    struct scalar_tag;
  
    template <typename T>
    struct tag_of<
      T
      , typename std::enable_if<
          std::is_arithmetic<T>::value
          && !std::is_const<T>::value // avoid conflict with tag_of<T const>
          >::type>
    {
      using type = scalar_tag;
    };

    template <typename T>
    struct tag_of<T const>: tag_of<T> {};
    template <typename T>
    struct tag_of<T&>: tag_of<T> {};
    template <typename T>
    struct tag_of<T&&>: tag_of<T> {};
  } // namespace traits
} // namespace geometry
} // namespace particle
