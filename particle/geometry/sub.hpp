#pragma once

// Particle headers
#include "../config.hpp"

// Boost headers
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

// Std headers
#include <type_traits>
#include <utility>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      struct sub
      {
        template <class> struct result;

        template <class F, class T0, class T1>
        struct result<F(T0, T1)>
        {
          typedef decltype(std::declval<T0>() + std::declval<T1>()) type;
        };

        template <class T0, class T1>
        PARTICLE_INLINE_FUNCTION
        auto operator()(T0 const& lhs, T1 const& rhs) const -> decltype(lhs - rhs)
        {
          return lhs - rhs;
        }
      };
    } // namespace detail

    template <
      class T0
      , class T1
      , typename std::enable_if<
          boost::fusion::result_of::size<T0>::value
          == boost::fusion::result_of::size<T1>::value
          , int
          >::type = 0
      >
    PARTICLE_INLINE_FUNCTION
    auto sub(T0 const& lhs, T1 const& rhs) ->
      decltype(boost::fusion::transform(lhs, rhs, detail::sub()))
    {
      return boost::fusion::transform(lhs, rhs, detail::sub());
    }
  } // namespace geometry
} // namespace particle
