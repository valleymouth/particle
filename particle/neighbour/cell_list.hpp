#pragma once

// Particle headers
#include <particle/geometry/add.hpp>

// Thrust headers
#include <thrust/binary_search.h>
#include <thrust/device_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/transform.h>

// Std headers
#include <iterator>

namespace particle
{
namespace neighbour
{
  template <typename Grid, typename Index = int>
  class cell_list
  {
    Grid m_grid;
    thrust::device_vector<Index> m_indices;
    thrust::device_vector<Index> m_cell_ranges; // for each cell gives its first particle index
  
  public:
    cell_list(const Grid& grid): m_grid(grid) {}
  
    template <typename InputIterator, typename RandomAccessIterator>
    void build(
      InputIterator position_first
      , InputIterator position_last
      , RandomAccessIterator attrs_first)
    {
      m_indices.resize(std::distance(position_first, position_last));

      // local copy to be used inside lambda and prevent copy of *this
      Grid grid = m_grid;

      // compute cell indices
      using value_type = typename std::iterator_traits<InputIterator>::value_type;
      thrust::transform(
        position_first
        , position_last
        , m_indices.begin()
        , PARTICLE_LAMBDA (const value_type& x)
        { return grid.get_index(grid.template get_cell_index<Index>(x)); });

      // sort collection based on cell indices
      thrust::sort_by_key(m_indices.begin(), m_indices.end(), attrs_first);

      // setup container storing cell ranges
      int cell_count = m_grid.cell_count();
      m_cell_ranges.resize(cell_count + 1);
      thrust::fill(m_cell_ranges.begin(), m_cell_ranges.begin() + 1, 0);

      // compute cell ranges
      thrust::upper_bound(
        m_indices.begin()
        , m_indices.end()
        , thrust::counting_iterator<Index>(0)
        , thrust::counting_iterator<Index>(cell_count)
        , m_cell_ranges.begin());
    }

    template <typename Position, typename F>
    void pair_interact(Position first, Position last, F f)
    {
      // local copy to be used inside lambda and prevent copy of *this
      auto ranges = m_cell_ranges.begin();
      auto grid = m_grid;

      thrust::for_each(
        thrust::counting_iterator<Index>(0)
        , thrust::counting_iterator<Index>(last - first)
        , PARTICLE_LAMBDA(Index i) {
          auto position = first + i;
          auto cell = grid.template get_cell_index<Index>(*position);
          for (Index yi = -1; yi <= 1; yi++)
          {
            for (Index xi = -1; xi <= 1; xi++)
            {
              Index index = grid.get_index(
                particle::geometry::add(cell, thrust::make_tuple(xi, yi)));
              for (Index ni = *(ranges + index); ni < *(ranges + index + 1); ni++)
              {
                f(i, ni);
              }
            }
          }
        });
    }
  };
} // namespace neighbour
} // namespace particle
  
