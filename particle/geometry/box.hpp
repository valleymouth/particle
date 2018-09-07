#pragma once

// Particle headers
#include "../config.hpp"

// Boost headers
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

// Std headers
#include <type_traits>

namespace particle
{
  namespace geometry
  {
    template <
      class Min
      , class Max = Min
      , typename std::enable_if<
          boost::fusion::traits::is_sequence<Min>::value &&
          boost::fusion::traits::is_sequence<Max>::value &&
          (boost::fusion::result_of::size<Min>::value
           == boost::fusion::result_of::size<Max>::value)
          , int
          >::type = 0
      >
    struct box
    {
      typedef Min min_type;
      typedef Max max_type;
      
      Min min;
      Max max;

      box(Min min, Max max): min(min), max(max)
      {}
      
      bool operator==(const box<Min, Max> &box) const
      {
	if (min = box.min && max == box.max)
	  return true;
	return false;
      }

      bool operator!=(const box<Min, Max> &box) const
      {
	return !((*this) == box);
      }
    };

    namespace traits
    {
      template <class>
      struct min;
    
      template <class Box>
      struct min
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<Box>
	  , const typename Box::min_type &
	  , typename Box::min_type &
	  >::type type;
      
	PARTICLE_INLINE_FUNCTION
	static type call(Box &box)
	{
	  return box.min;
	}
      };

      template <class>
      struct max;

      template <class Box>
      struct max
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<Box>
	  , const typename Box::max_type &
	  , typename Box::max_type &
	  >::type type;
      
	PARTICLE_INLINE_FUNCTION
	static type call(Box &box)
	{
	  return box.max;
	}
      };
    } // namespace traits
  } // namespace geometry
} // namespace particle
