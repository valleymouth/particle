#pragma once

// Particle headers
#include "../dim.hpp"
#include "../elem.hpp"
#include "../is_vector.hpp"
#include "../tag_of.hpp"

namespace particle
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
    template <typename T, std::size_t I>
    struct apply;

    template <>
    struct apply<0>
    {
      PARTICLE_STATIC_FUNCTION
      float call(float2& f)
      {
        return f.x;
      }
    };
    
    template <>
    struct apply<1>
    {
      PARTICLE_STATIC_FUNCTION
      float call(float2& f)
      {
        return f.y;
      }
    };
  };
} // namspace detail
} // namespace particle
