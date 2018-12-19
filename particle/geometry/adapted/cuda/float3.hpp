#pragma once

// Particle headers
#include "../../dim.hpp"
#include "../../elem.hpp"
#include "../../is_vector.hpp"
#include "../../tag_of.hpp"
#include "../../value_type.hpp"

namespace particle
{
namespace geometry
{
  namespace traits
  {
    struct cuda_float3_tag;

    template <>
    struct tag_of<float3>
    {
      using type = cuda_float3_tag;
    };

    template <>
    struct dim<float3>
    {
      static constexpr int value = 3;
    };

    template <>
    struct is_vector<float3>
    {
      static constexpr bool value = true;
    };

    template <>
    struct value_type<float3>
    {
      using type = float;
    };
  } // namespace traits

  namespace detail
  {
    template <>
    struct elem_impl<traits::cuda_float3_tag>
    {
      template <typename Float3, std::size_t I>
      struct apply;

      template <typename Float3>
      struct apply<Float3, 0>
      {
        PARTICLE_STATIC_FUNCTION
        float& call(float3& f)
        {
          return f.x;
        }

        PARTICLE_STATIC_FUNCTION
        const float& call(const float3& f)
        {
          return f.x;
        }

        PARTICLE_STATIC_FUNCTION
        float call(float3&& f)
        {
          return f.x;
        }
      };
    
      template <typename Float3>
      struct apply<Float3, 1>
      {
        PARTICLE_STATIC_FUNCTION
        float& call(float3& f)
        {
          return f.y;
        }

        PARTICLE_STATIC_FUNCTION
        const float& call(const float3& f)
        {
          return f.y;
        }

        PARTICLE_STATIC_FUNCTION
        float call(float3&& f)
        {
          return f.y;
        }
      };

      template <typename Float3>
      struct apply<Float3, 2>
      {
        PARTICLE_STATIC_FUNCTION
        float& call(float3& f)
        {
          return f.z;
        }

        PARTICLE_STATIC_FUNCTION
        const float& call(const float3& f)
        {
          return f.z;
        }

        PARTICLE_STATIC_FUNCTION
        float call(float3&& f)
        {
          return f.z;
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
