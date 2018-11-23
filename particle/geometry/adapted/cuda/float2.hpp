#pragma once

// Particle headers
#include "../../dim.hpp"
#include "../../elem.hpp"
#include "../../is_vector.hpp"
#include "../../tag_of.hpp"

namespace particle
{
namespace geometry
{
  namespace traits
  {
    struct cuda_float2_tag;

    template <>
    struct tag_of<float2>
    {
      using type = cuda_float2_tag;
    };

    template <>
    struct dim<float2>
    {
      static constexpr int value = 2;
    };

    template <>
    struct is_vector<float2>
    {
      static constexpr bool value = true;
    };
  } // namespace traits

  namespace detail
  {
    template <>
    struct elem_impl<traits::cuda_float2_tag>
    {
      template <typename Float2, std::size_t I>
      struct apply;

      template <typename Float2>
      struct apply<Float2, 0>
      {
        PARTICLE_STATIC_FUNCTION
        auto& call(Float2&& f)
        {
          return f.x;
        }
      };
    
      template <typename Float2>
      struct apply<Float2, 1>
      {
        PARTICLE_STATIC_FUNCTION
        auto& call(Float2&& f)
        {
          return f.y;
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
