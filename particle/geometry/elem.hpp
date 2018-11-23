#pragma once

// Particle headers
#include "../config.hpp"
#include "tag_of.hpp"

namespace particle
{
namespace geometry
{
  namespace detail
  {
    template <typename T>
    struct elem_impl;

    template <>
    struct elem_impl<traits::scalar_tag>
    {
      template <typename T, std::size_t>
      struct apply
      {
        PARTICLE_STATIC_FUNCTION
        typename std::conditional<
          std::is_const<T>::value
          , T const&
          , T&
          >::type call(T& x)
        {
          return x;
        }
      };
    };
  } // namespace detail

  template <std::size_t I, typename T>
  PARTICLE_INLINE_FUNCTION
  decltype(auto) elem(T& vec)
  {
    return detail::elem_impl<
      typename traits::tag_of<T>::type
      >::template apply<T, I>::call(vec);
  }
} // namespace geometry
} // namespace particle
