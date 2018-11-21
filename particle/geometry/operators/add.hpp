#pragma once

// Particle headers
#include "../add.hpp"

// Std headers
#include <type_traits>

namespace particle
{
namespace geometry
{
  template <
    class L
    , class R
    , typename std::enable_if<
        traits::is_vector<L>::value
        || traits::is_vector<R>::value
        , int
        >::type = 0
    >
  PARTICLE_INLINE_FUNCTION
  auto operator+(L&& lhs, R&& rhs)
  {
    return add(std::forward<L>(lhs), std::forward<R>(rhs));
  }
} // namespace geometry
} // namespace particle
