#pragma once

// Particle headers
#include "../config.hpp"
#include "dim.hpp"
#include "tag_of.hpp"

// Std headers
#include <type_traits>

namespace particle
{
namespace geometry
{
  template <typename Min, typename Max>
  struct box
  {
    using min_type = Min;
    using max_type = Max;
  
    Min min;
    Max max;

    PARTICLE_INLINE_FUNCTION
    box(Min const& min, Max const& max)
      : min(min), max(max)
    {}
  };

  namespace traits
  {
    struct box_tag;
    
    template <typename Min, typename Max>
    struct tag_of<box<Min, Max>>
    {
      using type = box_tag;
    };

    template <typename Min, typename Max>
    struct dim<box<Min, Max>>
    {
      static constexpr int value = dim<Min>::value;
    };
  } // namespace traits

  namespace detail
  {
    template <typename>
    struct max_impl;

    template <>
    struct max_impl<traits::box_tag>
    {
      template <typename T>
      PARTICLE_STATIC_FUNCTION
      auto& apply(T& b)
      {
        return b.max;
      }
    };

    template <typename>
    struct min_impl;

    template <>
    struct min_impl<traits::box_tag>
    {
      template <typename T>
      PARTICLE_STATIC_FUNCTION
      auto& apply(T& b)
      {
        return b.min;
      }
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
