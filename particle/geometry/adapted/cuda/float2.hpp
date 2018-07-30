#pragma once

// Particle headers
#include "../../../config.hpp"
#include "../../tags.hpp"

// Boost headers
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_const.hpp>

namespace particle
{
  namespace geometry
  {
    namespace traits
    {
      template <class>
      struct tag;

      template <>
      struct tag<float2>
	: boost::mpl::identity<tags::vector_tag>
      {};

      template <class>
      struct dimension;

      template <>
      struct dimension<float2>
	: boost::mpl::int_<2>
      {};

      template <class, std::size_t, class>
      struct elem;
      
      template <class T>
      struct elem<float2, 0, T>
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<T>, const float &, float &>::type type;

	PARTICLE_INLINE_FUNCTION
	static type call(T &v)
	{
	  return v.x;
	}
      };

      template <class T>
      struct elem<float2, 1, T>
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<T>, const float &, float &>::type type;

	PARTICLE_INLINE_FUNCTION
	static type call(T &v)
	{
	  return v.y;
	}
      };
    } // namespace traits
  } // namespace geometry
} // namespace particle
