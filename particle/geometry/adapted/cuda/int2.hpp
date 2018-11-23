#pragma once

// Particle headers
#include "../../config.hpp"

namespace particle
{
namespace geometry
{
  namespace traits
  {
    struct cuda_int2_tag;

    template <typename, typename Enable = void>
    struct tag_of;

    template <>
    struct tag_of<int2>
    {
      using type = cuda_int2_tag;
    };

    template <typename, typename Enable = void>
    struct dim;

    template <>
    struct dim<int2>
    {
      static constexpr int value = 2;
    };

    template <typename, typename Enable = void>
    struct is_vector;

    template <>
    struct is_vector<int2>
    {
      static constexpr bool value = true;
    };
  } // namespace traits

  namespace detail
  {
    template <typename>
    struct elem_impl;

    template <>
    struct elem_impl<traits::cuda_int2_tag>
    {
      template <typename Int2, std::size_t I>
      struct apply;

      template <typename Int2>
      struct apply<Int2, 0>
      {
        PARTICLE_STATIC_FUNCTION
        auto& call(Int2&& f)
        {
          return f.x;
        }
      };
    
      template <typename Int2>
      struct apply<Int2, 1>
      {
        PARTICLE_STATIC_FUNCTION
        auto& call(Int2&& f)
        {
          return f.y;
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
