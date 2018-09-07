#pragma once

// Particle headers
#include "../config.hpp"

// Boost headers
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace particle
{
  namespace geometry
  {
    template <class Min, class Max = Min>
    struct box
    {
      typedef Min min_type;
      typedef Max max_type;
      
      Min min;
      Max max;

      bool operator==(const box &box) const
      {
	if (min = box.min && max == box.max)
	  return true;
	return false;
      }

      bool operator!=(const box &box) const
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
