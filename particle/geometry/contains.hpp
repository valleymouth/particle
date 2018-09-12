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
      struct contains
      {
        template<
          class MinFirst
          , class MinLast
          , class MaxFirst
          , class PointFirst
          >
        PARTICLE_INLINE_FUNCTION
        static bool call(
          MinFirst const& min_first
          , MinLast const& min_last
          , MaxFirst const& max_first
          , PointFirst const& point_first
          , boost::mpl::true_
          )
        {
          return true;
        }
        
        template<
          class MinFirst
          , class MinLast
          , class MaxFirst
          , class PointFirst
          >
        PARTICLE_INLINE_FUNCTION
        static bool call(
          MinFirst const& min_first
          , MinLast const& min_last
          , MaxFirst const& max_first
          , PointFirst const& point_first
          , boost::mpl::false_
          )
        {
          namespace fu = boost::fusion;
          return *min_first <= *point_first
            && *max_first > *point_first
            && call(
              fu::next(min_first)
              , min_last
              , fu::next(max_first)
              , fu::next(point_first)
              , fu::result_of::equal_to<
              typename fu::result_of::next<MinFirst>::type
              , MinLast>());
        }

        template <class Box, class Point>
        PARTICLE_INLINE_FUNCTION
        static bool call(Box const& box, Point const& p)
        {
          typedef typename Box::min_type min_type;
          namespace fu = boost::fusion;
          return call(
            fu::begin(min(box))
            , fu::end(min(box))
            , fu::begin(max(box))
            , fu::begin(p)
            , fu::result_of::equal_to<
            typename fu::result_of::begin<min_type>::type
            , typename fu::result_of::end<min_type>::type>());
        }
      };
    } // namespace detail

    template <class Box, class Point>
    PARTICLE_INLINE_FUNCTION
    bool contains(Box const& box, Point const& p)
    {
      return detail::contains::call(box, p);
    }
  } // namespace geometry
} // namespace particle
