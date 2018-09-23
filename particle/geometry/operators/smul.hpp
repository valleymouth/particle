#pragma once

// Local headers
#include "../smul.hpp"

// Boost headers
#include <boost/fusion/support/is_sequence.hpp>

// Std headers
#include <type_traits>

namespace particle
{
  namespace geometry
  {
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
