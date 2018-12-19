#pragma once

// Particle headers
#include "../config.hpp"
#include "tag_of.hpp"

// Std headers
#include <utility> // for std::forward

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
        decltype(auto) call(T&& x)
        {
          return std::forward<T>(x);
        }
      };
    };
  } // namespace detail

  template <std::size_t I, typename T>
  PARTICLE_INLINE_FUNCTION
  decltype(auto) elem(T&& vec)
  {
    return detail::elem_impl<
      typename traits::tag_of<T>::type
      >::template apply<T, I>::call(std::forward<T>(vec));
  }
} // namespace geometry
} // namespace particle
