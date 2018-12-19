#pragma once

// Particle headers
#include "../../dim.hpp"
#include "../../elem.hpp"
#include "../../is_vector.hpp"
#include "../../tag_of.hpp"
#include "../../value_type.hpp"

// Cuda headers
#include <thrust/tuple.h>

// Std headers
#include <utility>

namespace particle
{
namespace geometry
{
  namespace traits
  {
    struct thrust_tuple_tag;

    template <typename... T>
    struct tag_of<thrust::tuple<T...>>
    {
      using type = thrust_tuple_tag;
    };

    template <typename... T>
    struct dim<thrust::tuple<T...>>
    {
      static constexpr int value =
        thrust::tuple_size<thrust::tuple<T...>>::value;
    };

    template <typename... T>
    struct is_vector<thrust::tuple<T...>>
    {
      static constexpr bool value = true;
    };

    template <typename... T>
    struct value_type<thrust::tuple<T...>>
    {
      // Using the first type as we consider that all types will be the same
      // in the geometry context
      using type = typename std::remove_cv<
        typename std::remove_reference<
          decltype(thrust::get<0>(std::declval<thrust::tuple<T...>>()))
          >::type>::type;
    };
  } // namespace traits

  namespace detail
  {
    template <typename>
    struct elem_impl;

    template <>
    struct elem_impl<traits::thrust_tuple_tag>
    {
      template <typename T, std::size_t I>
      struct apply
      {
        PARTICLE_STATIC_FUNCTION
        decltype(auto) call(T&& x)
        {
          return std::forward<
            decltype(thrust::get<I>(std::forward<T>(x)))
            >(thrust::get<I>(std::forward<T>(x)));
        }
      };
    };
  } // namespace detail
} // namespace geometry
} // namespace particle
