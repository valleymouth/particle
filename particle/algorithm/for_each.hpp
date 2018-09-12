#pragma once

// Particle headers
#include "../config.hpp"
#include "../geometry/max.hpp"
#include "../geometry/min.hpp"

// Boost headers
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/bool.hpp>

namespace particle
{
  namespace detail
  {
    struct for_each
    {
      template <
        class MinFirst
        , class MinLast
        , class MaxFirst
        , class UnaryFunction
        , class... Index
        >
      PARTICLE_INLINE_FUNCTION
      static void call(
        MinFirst const& min_first
        , MinLast const& min_last
        , MaxFirst const& max_first
        , UnaryFunction f
        , boost::mpl::true_
        , Index... index)
      {
        f(index...);
      }

      template <
        class MinFirst
        , class MinLast
        , class MaxFirst
        , class UnaryFunction
        , class... Index
        >
      PARTICLE_INLINE_FUNCTION
      static void call(
        MinFirst const& min_first
        , MinLast const& min_last
        , MaxFirst const& max_first
        , UnaryFunction f
        , boost::mpl::false_
        , Index... index)
      {
        namespace fu = boost::fusion;
        for(auto i = *min_first; i < *max_first; i++)
        {
          call(
            fu::next(min_first)
            , min_last
            , fu::next(max_first)
            , f
            , fu::result_of::equal_to<
            typename fu::result_of::next<MinFirst>::type
            , MinLast>()
            , index...
            , i
            );
        }
      } 

      template <class Box, class UnaryFunction>
      PARTICLE_INLINE_FUNCTION
      static void call(Box const& box, UnaryFunction f)
      {
        typedef typename Box::min_type min_type;
        namespace fu = boost::fusion;
        call(
          fu::begin(geometry::min(box))
          , fu::end(geometry::min(box))
          , fu::begin(max(box))
          , f
          , fu::result_of::equal_to<
          typename fu::result_of::begin<min_type>::type
          , typename fu::result_of::end<min_type>::type>());
      }
    };
  }
  
  template <class Box, class UnaryFunction>
  PARTICLE_INLINE_FUNCTION
  void for_each(Box const& box, UnaryFunction f)
  {
    detail::for_each::call(box, f);
  }
}
