#pragma once

// Particle headers
#include "box.hpp"

namespace particle
{
namespace geometry
{
  template <typename Min, typename Max>
  PARTICLE_INLINE_FUNCTION
  auto make_box(Min&& min, Max&& max)
  {
    // using min_type = decltype(std::forward<Min>(min));
    // using max_type = decltype(std::forward<Max>(max));
    //BOOST_MPL_ASSERT((std::is_same<int, Min>));
    return box<
      typename std::conditional<
        std::is_lvalue_reference<Min>::value
        , Min&
        , Min>::type
      , typename std::conditional<
        std::is_lvalue_reference<Max>::value
          , Max&
          , Max>::type
      >(std::forward<Min>(min), std::forward<Max>(max));
    using min_type = decltype(std::forward<Min>(min));
    using max_type = decltype(std::forward<Max>(max));
    // return box<min_type, max_type>(std::forward<Min>(min), std::forward<Max>(max));
  }
} // namespace geometry
} // namespace particle
