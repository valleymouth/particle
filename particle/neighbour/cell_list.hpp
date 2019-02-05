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
  template <typename Grid, typename Container>
  class cell_list
  {
    using index_type = typename Container::value_type;
    
    Grid m_grid;
    Container m_indices;
    Container m_cell_ranges; // for each cell stores its first particle index

  public:
    struct neighbour_list
    {
      Grid grid;
      typename Container::iterator ranges;
      
      template <typename Position, typename T, typename F>
      __device__
      auto reduce(index_type i, const Position& p, const T& init, F f)
      {
        T result = init;
        auto cell = grid.template get_cell_index<index_type>(p);
        for (index_type yi = -1; yi <= 1; yi++)
        {
          for (index_type xi = -1; xi <= 1; xi++)
          {
            index_type index = grid.get_index(
              particle::geometry::add(cell, thrust::make_tuple(xi, yi)));
              for (index_type j = *(ranges + index); j < *(ranges + index + 1); j++)
              {
                if (i != j)
                  f(i, j, result);
              }
          }
        }
        return result;
      }
    };

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
        { return grid.get_index(grid.template get_cell_index<index_type>(x)); });

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
        , thrust::counting_iterator<index_type>(0)
        , thrust::counting_iterator<index_type>(cell_count)
        , m_cell_ranges.begin() + 1);
    }

    template <typename InputIterator, typename F>
    void pair_interact(
      InputIterator position_first
      , InputIterator position_last
      , F f)
    {
      neighbour_list nl = {m_grid, m_cell_ranges.begin()};
      thrust::for_each(
        thrust::counting_iterator<index_type>(0)
        , thrust::counting_iterator<index_type>(position_last - position_first)
        , [=] __device__ (index_type i)
        {
          f(i, nl);
        });
    }
  };
} // namespace neighbour
} // namespace particle
  
