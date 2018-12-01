#pragma once

// Particle headers
#include "../config.hpp"
#include "../geometry/dim.hpp"
#include "../geometry/elem.hpp"
#include "../geometry/min.hpp"
#include "../geometry/size.hpp"
#include "../geometry/sub.hpp"

namespace particle
{
namespace grid
{
  namespace detail
  {
    template <int I>
    struct right_impl_
    {
      template <typename Index, typename Size, typename Stride>
      PARTICLE_STATIC_FUNCTION
      auto apply(const Index& i, const Size& size, const Stride& stride)
      {
        using geometry::elem;
        return elem<I>(i) * stride + right_impl_<I - 1>::apply(i, size, elem<I>(size) * stride);
      }
    };

    template <>
    struct right_impl_<0>
    {
      template <typename Index, typename Size, typename Stride>
      PARTICLE_STATIC_FUNCTION
      auto apply(const Index& i, const Size&, const Stride& stride)
      {
        return geometry::elem<0>(i) * stride;
      }
    };
    
    template <typename Box, typename Cell>
    PARTICLE_INLINE_FUNCTION
    auto right_impl(const Box& box, const Cell& cell)
    {
      using geometry::min;
      using geometry::size;
      using geometry::sub;
      return detail::right_impl_<
        geometry::traits::dim<Box>::value - 1
        >::apply(sub(cell, min(box)), size(box), 1);
    }
  } // namespace detail
  
  template <typename Box, typename Cell>
  PARTICLE_INLINE_FUNCTION
  auto right(const Box& box, const Cell& cell)
  {
    return detail::right_impl(box, cell);
  }
} // namespace grid
} // namespace particle
