#pragma once

// Particle headers
#include "../../dim.hpp"
#include "../../elem.hpp"
#include "../../is_vector.hpp"
#include "../../tag_of.hpp"
#include "../../value_type.hpp"

namespace particle
{
namespace geometry
{
  namespace traits
  {
    struct cuda_double2_tag;

    template <>
    struct tag_of<double2>
    {
      using type = cuda_double2_tag;
    };

    template <>
    struct dim<double2>
    {
      static constexpr int value = 2;
    };

    template <>
    struct is_vector<double2>
    {
      static constexpr bool value = true;
    };

    template <>
    struct value_type<double2>
    {
      using type = double;
    };
  } // namespace traits

  namespace detail
  {
    template <>
    struct elem_impl<traits::cuda_double2_tag>
    {
      template <typename Double2, std::size_t I>
      struct apply;

      template <typename Double2>
      struct apply<Double2, 0>
      {
        PARTICLE_STATIC_FUNCTION
        double& call(double2& f)
        {
          return f.x;
        }

        PARTICLE_STATIC_FUNCTION
        const double& call(const double2& f)
        {
          return f.x;
        }

        PARTICLE_STATIC_FUNCTION
        double call(double2&& f)
        {
          return f.x;
        }
      };
    
      template <typename Double2>
      struct apply<Double2, 1>
      {
        PARTICLE_STATIC_FUNCTION
        double& call(double2& f)
        {
          return f.y;
        }

        PARTICLE_STATIC_FUNCTION
        const double& call(const double2& f)
        {
          return f.y;
        }

        PARTICLE_STATIC_FUNCTION
        double call(double2&& f)
        {
          return f.y;
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
