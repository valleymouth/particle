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
    struct cuda_int2_tag;

    template <>
    struct tag_of<int2>
    {
      using type = cuda_int2_tag;
    };

    template <>
    struct dim<int2>
    {
      static constexpr int value = 2;
    };

    template <>
    struct is_vector<int2>
    {
      static constexpr bool value = true;
    };

    template <>
    struct value_type<int2>
    {
      using type = int;
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
        int& call(int2& f)
        {
          return f.x;
        }

        PARTICLE_STATIC_FUNCTION
        const int& call(const int2& f)
        {
          return f.x;
        }

        PARTICLE_STATIC_FUNCTION
        int call(int2&& f)
        {
          return f.x;
        }
      };
    
      template <typename Int2>
      struct apply<Int2, 1>
      {
        PARTICLE_STATIC_FUNCTION
        int& call(int2& f)
        {
          return f.y;
        }

        PARTICLE_STATIC_FUNCTION
        const int& call(const int2& f)
        {
          return f.y;
        }

        PARTICLE_STATIC_FUNCTION
        int call(int2&& f)
        {
          return f.y;
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
