#pragma once

// Particle headers
#include "../config.hpp"
#include "../geometry/max.hpp"
#include "../geometry/min.hpp"

// Boost headers
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_list.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits.hpp>

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
        for(auto i = *min_first; i < *max_first; i++)
        {
          call(
            boost::fusion::next(min_first)
            , min_last
            , boost::fusion::next(max_first)
            , f
            , boost::fusion::result_of::equal_to<
            typename boost::fusion::result_of::next<MinFirst>::type
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
        call(
          boost::fusion::begin(geometry::min(box))
          , boost::fusion::end(geometry::min(box))
          , boost::fusion::begin(max(box))
          , f
          , boost::fusion::result_of::equal_to<
          typename boost::fusion::result_of::begin<
          typename Box::min_type
          >::type
          , typename boost::fusion::result_of::end<
          typename Box::min_type
          >::type
          >());
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
