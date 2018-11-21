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
      template <typename T, std::size_t I>
      struct apply;

      template <>
      struct apply<0>
      {
        PARTICLE_STATIC_FUNCTION
        int call(int2& f)
        {
          return f.x;
        }
      };
    
      template <>
      struct apply<1>
      {
        PARTICLE_STATIC_FUNCTION
        int call(int2& f)
        {
          return f.y;
        }
      };
    };
  } // namspace detail
} // namespace geometry
} // namespace particle
