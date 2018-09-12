#pragma once

// Local headers
#include "max.hpp"
#include "min.hpp"

// Boost headers
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/bool.hpp>

namespace particle
{
  namespace geometry
  {
    namespace detail
    {
      struct is_empty
      {
        template<
          class MinFirst
          , class MinLast
          , class MaxFirst
          >
        PARTICLE_INLINE_FUNCTION
        static bool call(
          MinFirst const& min_first
          , MinLast const& min_last
          , MaxFirst const& max_first
          , boost::mpl::true_
          )
        {
          return false;
        }
        
        template<
          class MinFirst
          , class MinLast
          , class MaxFirst
          >
        PARTICLE_INLINE_FUNCTION
        static bool call(
          MinFirst const& min_first
          , MinLast const& min_last
          , MaxFirst const& max_first
          , boost::mpl::false_
          )
        {
          namespace fu = boost::fusion;
          return *min_first >= *max_first
            || call(
              fu::next(min_first)
              , min_last
              , fu::next(max_first)
              , fu::result_of::equal_to<
              typename fu::result_of::next<MinFirst>::type
              , MinLast>());
        }

        template <class Box>
        PARTICLE_INLINE_FUNCTION
        static bool call(Box const& box)
        {
          typedef typename Box::min_type min_type;
          namespace fu = boost::fusion;
          return call(
            fu::begin(min(box))
            , fu::end(min(box))
            , fu::begin(max(box))
            , fu::result_of::equal_to<
            typename fu::result_of::begin<min_type>::type
            , typename fu::result_of::end<min_type>::type>());
        }
      };
    } // namespace detail

    template <class Box>
    PARTICLE_INLINE_FUNCTION
    bool is_empty(const Box &box)
    {
      return detail::is_empty::call(box);
    }
  } // namespace geometry
} // namespace particle
