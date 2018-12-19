#pragma once

// Particle headers
#include "../config.hpp"
#include "../geometry/cast.hpp"
#include "../geometry/div.hpp"
#include "../geometry/fold.hpp"
#include "../geometry/size.hpp"

namespace particle
{
  template <typename Box, typename CellSize, typename Derived>
  struct grid
  {
    Box box;
    CellSize cell_size;
  
    grid(const Box& box, const CellSize& cell_size)
      : box(box), cell_size(cell_size) {}

    // Get sequential index
    template <typename Cell>
    PARTICLE_INLINE_FUNCTION
    auto get_index(const Cell& cell) const
    {
      return static_cast<const Derived*>(this)->get_index(cell);
    }

    PARTICLE_INLINE_FUNCTION
    auto cell_count() const
    {
      using particle::geometry::fold;
      using particle::geometry::size;
      return fold(size(box), 1, [](auto s, auto x) { return s * x; });
    }

    // Get multi-dimentional cell index
    template <typename Index, typename Position>
    PARTICLE_INLINE_FUNCTION
    auto get_cell_index(const Position& x) const
    {
      using particle::geometry::cast;
      using particle::geometry::div;
      return cast<Index>(div(x, cell_size));
    }
  };
} // namespace particle
