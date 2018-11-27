#pragma once

// Particle headers
#include "../config.hpp"

namespace particle
{
namespace geometry
{
  namespace detail
  {
    template <typename>
    struct min_impl;
  } // namespace detail

  template <typename Box>
  PARTICLE_INLINE_FUNCTION
  decltype(auto) min(Box&& b)
  {
    return detail::min_impl<
      typename traits::tag_of<Box>::type
      >::apply(std::forward<Box>(b));
  }
} // namespace geometry
} // namespace particle
