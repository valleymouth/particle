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
    template <int I, int N>
    struct left_impl_
    {
      template <typename Index, typename Size, typename Stride>
      PARTICLE_STATIC_FUNCTION
      auto apply(const Index& i, const Size& size, const Stride& stride)
      {
        using geometry::elem;
        return elem<I>(i) * stride + left_impl_<I + 1, N>::apply(i, size, elem<I>(size) * stride);
      }
    };

    template <int N>
    struct left_impl_<N, N>
    {
      template <typename Index, typename Size, typename Stride>
      PARTICLE_STATIC_FUNCTION
      auto apply(const Index& i, const Size&, const Stride& stride)
      {
        return geometry::elem<N>(i) * stride;
      }
    };
    
    template <typename Box, typename Cell>
    PARTICLE_INLINE_FUNCTION
    auto left_impl(const Box& box, const Cell& cell)
    {
      using geometry::min;
      using geometry::size;
      using geometry::sub;
      return detail::left_impl_<
        0
        , geometry::traits::dim<Box>::value - 1
        >::apply(sub(cell, min(box)), size(box), 1);
    }
  } // namespace detail
  
  template <typename Box, typename Cell>
  PARTICLE_INLINE_FUNCTION
  auto left(const Box& box, const Cell& cell)
  {
    return detail::left_impl(box, cell);
  }
} // namespace grid
} // namespace particle
