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
    struct cuda_int3_tag;

    template <>
    struct tag_of<int3>
    {
      using type = cuda_int3_tag;
    };

    template <>
    struct dim<int3>
    {
      static constexpr int value = 3;
    };

    template <>
    struct is_vector<int3>
    {
      static constexpr bool value = true;
    };
  } // namespace traits

  namespace detail
  {
    template <>
    struct elem_impl<traits::cuda_int3_tag>
    {
      template <typename Int3, std::size_t I>
      struct apply;

      template <typename Int3>
      struct apply<Int3, 0>
      {
        PARTICLE_STATIC_FUNCTION
        auto& call(Int3&& f)
        {
          return f.x;
        }
      };
    
      template <typename Int3>
      struct apply<Int3, 1>
      {
        PARTICLE_STATIC_FUNCTION
        auto& call(Int3&& f)
        {
          return f.y;
        }
      };

      template <typename Int3>
      struct apply<Int3, 2>
      {
        PARTICLE_STATIC_FUNCTION
        auto& call(Int3&& f)
        {
          return f.z;
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
