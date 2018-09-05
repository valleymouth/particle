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
      struct minus
      {
        template <class> struct result;

        template <class F, class T0, class T1>
        struct result<F(T0, T1)>
        {
          typedef decltype(std::declval<T0>() + std::declval<T1>()) type;
        };

        template <class T0, class T1>
        PARTICLE_INLINE_FUNCTION
        auto operator()(const T0& lhs, const T1& rhs) const -> decltype(lhs - rhs)
        {
          return lhs - rhs;
        }
      };
    }

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
    auto minus(const T0 &lhs, const T1 &rhs) ->
      decltype(boost::fusion::transform(lhs, rhs, detail::minus()))
    {
      return boost::fusion::transform(lhs, rhs, detail::minus());
    }
  } // namespace geometry
} // namespace particle
