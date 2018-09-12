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
      struct convert
      {
        template <class> struct result;

        template <class F, class T0>
        struct result<F(T0)>
        {
          typedef T type;
        };

        template <class T0>        
        PARTICLE_INLINE_FUNCTION
        T operator()(T0 const& x) const
        {
          return T(x);
        }
      };
    } // namespace detail
    
    template <
      class T
      , class Sequence
      , typename std::enable_if<
          boost::fusion::traits::is_sequence<Sequence>::value
          , int
          >::type = 0
      >
    auto convert(Sequence const& sequence)
      -> decltype(boost::fusion::transform(sequence, detail::convert<T>()))
    {
      return boost::fusion::transform(sequence, detail::convert<T>());
    }
  } // namespace geometry
} // namespace particle
