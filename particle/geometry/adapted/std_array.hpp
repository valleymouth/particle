#pragma once

// Particle headers
#include "../dim.hpp"
#include "../elem.hpp"
#include "../is_vector.hpp"
#include "../tag_of.hpp"

// Std headers
#include <array>

namespace particle
{
namespace geometry
{
  namespace traits
  {
    struct std_array_tag;

    template <typename T, std::size_t N>
    struct tag_of<std::array<T, N>>
    {
      using type = std_array_tag;
    };

    template <typename T, std::size_t N>
    struct dim<std::array<T, N>>
    {
      static constexpr int value = N;
    };

    template <typename T, std::size_t N>
    struct is_vector<std::array<T, N>>
    {
      static constexpr bool value = true;
    };
  } // namespace traits

  namespace detail
  {
    template <>
    struct elem_impl<traits::std_array_tag>
    {
      template <std::size_t I>
      struct apply
      {
        // template <typename T>
        // PARTICLE_STATIC_FUNCTION
        // typename std::conditional<
        //   std::is_const<T>::value
        //   , typename T::value_type const&
        //   , typename T::value_type&
        //   >::type call(T& x)
        // {
        //   return x[I];
        // }
        template <typename T>
        PARTICLE_STATIC_FUNCTION
        auto& call(T& x)
        {
          return x[I];
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
