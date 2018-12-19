#pragma once

// Particle headers
#include "../../dim.hpp"
#include "../../elem.hpp"
#include "../../is_vector.hpp"
#include "../../tag_of.hpp"
#include "../../value_type.hpp"

// Cuda headers
#include <thrust/iterator/zip_iterator.h>
#include <thrust/device_reference.h>

namespace particle
{
namespace geometry
{
  namespace traits
  {
    struct thrust_zip_iterator_tag;

    template <typename... T>
    struct tag_of<thrust::detail::tuple_of_iterator_references<T...>>
    {
      using type = thrust_zip_iterator_tag;
    };

    template <typename... T>
    struct dim<thrust::detail::tuple_of_iterator_references<T...>>
    {
      static constexpr int value =
        thrust::tuple_size<thrust::detail::tuple_of_iterator_references<T...>>::value;
    };

    template <typename... T>
    struct is_vector<thrust::detail::tuple_of_iterator_references<T...>>
    {
      static constexpr bool value = true;
    };

    template <typename... T>
    struct value_type<thrust::detail::tuple_of_iterator_references<T...>>
    {
      // Using the first type as we consider that all types will be the same
      // in the geometry context
      using type = typename std::remove_cv<
        typename std::remove_reference<
          decltype(thrust::get<0>(
                     std::declval<
                     thrust::detail::tuple_of_iterator_references<T...>
                     >()))>::type>::type::value_type;
    };
  } // namespace traits

  namespace detail
  {
    template <typename>
    struct elem_impl;

    template <>
    struct elem_impl<traits::thrust_zip_iterator_tag>
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
