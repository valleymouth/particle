#pragma once

// Particle headers
#include "grid.hpp"
#include "left.hpp"

namespace particle
{
  template <typename Box, typename CellSize>
  struct left_grid: grid<Box, CellSize, left_grid<Box, CellSize>>
  {
    using base = grid<Box, CellSize, left_grid<Box, CellSize>>;
    left_grid(const Box& box, const CellSize& cell_size)
      : base(box, cell_size) {}

    template <typename Cell>
    PARTICLE_INLINE_FUNCTION
    auto get_index(const Cell& cell) const
    {
      return particle::sfc::left(base::box, cell);
    }
  };
} // namespace particle
