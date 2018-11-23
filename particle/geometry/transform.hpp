#pragma once

// Particle headers
#include "../config.hpp"
#include "dim.hpp"
#include "elem.hpp"
#include "is_vector.hpp"
#include "tag_of.hpp"

namespace particle
{
namespace geometry
{  
  namespace detail
  {
    template <typename T, typename F>
    struct unary_transform_t
    {
      typename std::conditional<
        std::is_rvalue_reference<T>::value
        , typename std::remove_reference<T>::type
        , T&
        >::type vec;
      typename std::conditional<
        std::is_rvalue_reference<F>::value
        , typename std::remove_reference<F>::type
        , F&
        >::type f;

      PARTICLE_INLINE_FUNCTION
      unary_transform_t(T&& x, F&& f)
        : vec(std::forward<T>(x))
        , f(std::forward<F>(f))
      {}
    };

    template <typename T0, typename T1, typename F>
    struct binary_transform_t
    {
      typename std::conditional<
        std::is_rvalue_reference<T0>::value
        , typename std::remove_reference<T0>::type
        , T0&
        >::type vec0;
      typename std::conditional<
        std::is_rvalue_reference<T1>::value
        , typename std::remove_reference<T1>::type
        , T1&
        >::type vec1;
      typename std::conditional<
        std::is_rvalue_reference<F>::value
        , typename std::remove_reference<F>::type
        , F&
        >::type f;

      PARTICLE_INLINE_FUNCTION
      binary_transform_t(T0&& x0, T1&& x1, F&& f)
        : vec0(std::forward<T0>(x0))
        , vec1(std::forward<T1>(x1))
        , f(std::forward<F>(f))
      {}
    };
  } // namespace detail

  namespace traits
  {
    struct unary_transform_tag;
    struct binary_transform_tag;

    template <typename T, typename F>
    struct tag_of<detail::unary_transform_t<T, F>>
    {
      using type = unary_transform_tag;
    };

    template <typename T, typename F>
    struct dim<detail::unary_transform_t<T, F>>
    {
      static constexpr int value = dim<T>::value;
    };

    template <typename T, typename F>
    struct is_vector<detail::unary_transform_t<T, F>>
    {
      static constexpr int value = true;
    };

    template <typename T0, typename T1, typename F>
    struct tag_of<detail::binary_transform_t<T0, T1, F>>
    {
      using type = binary_transform_tag;
    };

    template <typename T0, typename T1, typename F>
    struct dim<detail::binary_transform_t<T0, T1, F>>
    {
      static constexpr int value = dim<T0>::value;
    };

    template <typename T0, typename T1, typename F>
    struct is_vector<detail::binary_transform_t<T0, T1, F>>
    {
      static constexpr int value = true;
    };
  } // namespace traits

  namespace detail
  {
    template <>
    struct elem_impl<traits::unary_transform_tag>
    {
      template <typename T, std::size_t I>
      struct apply
      {
        PARTICLE_STATIC_FUNCTION
        decltype(auto) call(T&& x)
        {
          return x.f(elem<I>(x.vec));
        }
      };
    };

    template <>
    struct elem_impl<traits::binary_transform_tag>
    {
      template <typename T, std::size_t I>
      struct apply
      {
        PARTICLE_STATIC_FUNCTION
        decltype(auto) call(T&& x)
        {
          return x.f(elem<I>(x.vec0), elem<I>(x.vec1));
        }
      };
    };
  } // namespace detail
  
  template <typename T, typename F>
  PARTICLE_INLINE_FUNCTION
  auto transform(T&& x, F&& f)
  {
    return detail::unary_transform_t<
      decltype(std::forward<T>(x))
      , decltype(std::forward<F>(f))>(
        std::forward<T>(x)
        , std::forward<F>(f));
  }

  template <typename T0, typename T1, typename F>
  PARTICLE_INLINE_FUNCTION
  auto transform(T0&& x0, T1&& x1, F&& f)
  {
    return detail::binary_transform_t<
      decltype(std::forward<T0>(x0))
      , decltype(std::forward<T1>(x1))
      , decltype(std::forward<F>(f))>(
        std::forward<T0>(x0)
        , std::forward<T1>(x1)
        , std::forward<F>(f));
  }
} // namespace geometry
} // namespace particle
