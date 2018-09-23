#pragma once

// Local headers
#include "../sdiv.hpp"

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
    auto operator/(Sequence const& lhs, T const& rhs)
      -> decltype(sdiv(lhs, rhs))
    {
      return sdiv(lhs, rhs);
    }
  } // namespace geometry
} // namespace particle
