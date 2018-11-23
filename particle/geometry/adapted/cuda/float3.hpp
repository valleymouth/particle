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
        typename std::conditional<
          std::is_const<Float3>::value
          , float const&
          , float&>::type call(Float3& f)
          float call(float3& f)
        {
          return f.x;
        }
      };
    
      template <typename Float3>
      struct apply<Float3, 1>
      {
        PARTICLE_STATIC_FUNCTION
        typename std::conditional<
          std::is_const<Float3>::value
          , float const&
          , float&>::type call(Float3& f)
          float call(float3& f)
        {
          return f.y;
        }
      };

      template <typename Float3>
      struct apply<Float3, 2>
      {
        PARTICLE_STATIC_FUNCTION
        typename std::conditional<
          std::is_const<Float3>::value
          , float const&
          , float&>::type call(Float3& f)
          float call(float3& f)
        {
          return f.z;
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
