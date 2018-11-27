#pragma once

// Particle headers
#include "../config.hpp"
#include "dim.hpp"
#include "is_box.hpp"
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
    box(Min min, Max max)
      : min(min), max(max)
    {}

    PARTICLE_INLINE_FUNCTION
    box() = default;
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

    template <typename Min, typename Max>
    struct is_box<box<Min, Max>>
    {
      static constexpr int value = true;
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
      typename T::max_type& apply(T& b)
      {
        return b.max;
      }

      template <typename T>
      PARTICLE_STATIC_FUNCTION
      const typename T::max_type& apply(const T& b)
      {
        return b.max;
      }

      template <typename T>
      PARTICLE_STATIC_FUNCTION
      typename T::max_type apply(T&& b)
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
      typename T::min_type& apply(T& b)
      {
        return b.min;
      }

      template <typename T>
      PARTICLE_STATIC_FUNCTION
      const typename T::min_type& apply(const T& b)
      {
        return b.min;
      }

      template <typename T>
      PARTICLE_STATIC_FUNCTION
      typename T::min_type apply(T&& b)
      {
        return b.min;
      }
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
