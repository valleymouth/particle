#pragma once

// Local headers
#include "../add.hpp"

// Boost headers
#include <boost/fusion/support/is_sequence.hpp>

// Std headers
#include <type_traits>

namespace particle
{
  namespace geometry
  {
    template <
      class T0
      , class T1
      , typename std::enable_if<
          boost::fusion::traits::is_sequence<T0>::value
          && boost::fusion::traits::is_sequence<T1>::value
          , int
          >::type = 0
      >
    auto operator+(T0 const& a, T1 const& b) -> decltype(add(a, b))
    {
      return add(a, b);
    }
  } // namespace geometry
} // namespace particle