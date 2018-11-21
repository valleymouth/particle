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
    template <typename T, std::size_t I>
    struct apply;

    template <>
    struct apply<0>
    {
      PARTICLE_STATIC_FUNCTION
      int call(int3& f)
      {
        return f.x;
      }
    };
    
    template <>
    struct apply<1>
    {
      PARTICLE_STATIC_FUNCTION
      int call(int3& f)
      {
        return f.y;
      }
    };

    template <>
    struct apply<2>
    {
      PARTICLE_STATIC_FUNCTION
      int call(int3& f)
      {
        return f.z;
      }
    };
  };
} // namspace detail
} // namespace particle
