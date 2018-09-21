#pragma once

// Particle headers
#include "../config.hpp"

// Boost headers
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>

// Std headers
#include <type_traits>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      template <class T>
      struct smul
      {
        T const value;
        
        PARTICLE_INLINE_FUNCTION
        smul(T const& v): value(v) {}
        
        template <class> struct result;

        template <class F, class T0>
        struct result<F(T0)>
        {
          typedef decltype(std::declval<T0>() * std::declval<T>()) type;
        };

        template <class T0>        
        PARTICLE_INLINE_FUNCTION
        auto operator()(T0 const& lhs) const -> decltype(lhs * value)
        {
          return lhs * value;
        }
      };
    } // namespace detail
    
    template <
      class Sequence
      , class T
      , typename std::enable_if<
          boost::fusion::traits::is_sequence<Sequence>::value
          && std::is_arithmetic<T>::value
          , int
          >::type = 0
      >
    auto smul(Sequence const& lhs, T const& rhs)
      -> decltype(boost::fusion::transform(lhs, detail::smul<T>(rhs)))
    {
      return boost::fusion::transform(lhs, detail::smul<T>(rhs));
    }

    template <
      class Sequence
      , class T
      , typename std::enable_if<
          boost::fusion::traits::is_sequence<Sequence>::value
          && std::is_arithmetic<T>::value
          , int
          >::type = 0
      >
    auto operator*(Sequence const& lhs, T const& rhs)
      -> decltype(smul(lhs, rhs))
    {
      return smul(lhs, rhs);
    }

    template <
      class T
      , class Sequence
      , typename std::enable_if<
          boost::fusion::traits::is_sequence<Sequence>::value
          && std::is_arithmetic<T>::value
          , int
          >::type = 0
      >
    auto operator*(T const& lhs, Sequence const& rhs)
      -> decltype(smul(rhs, lhs))
    {
      return smul(rhs, lhs);
    }
  } // namespace geometry
} // namespace particle
