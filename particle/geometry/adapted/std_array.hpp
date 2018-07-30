#pragma once

// Particle headers
#include "../../config.hpp"
#include "../tags.hpp"

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

      template <class T, std::size_t N>
      struct tag<std::array<T, N>>
	: boost::mpl::identity<tags::vector_tag>
      {};

      template <class>
      struct dimension;

      template <class T, std::size_t N>
      struct dimension<std::array<T, N>>
	: boost::mpl::int_<N>
      {};

      template <class, std::size_t, class>
      struct elem;

      template <class T, std::size_t N, std::size_t I, class U>
      struct elem<std::array<T, N>, I, U>
      {
	typedef typename boost::mpl::if_<
	  boost::is_const<U>, const T &, T &>::type type;

	PARTICLE_INLINE_FUNCTION
	static constexpr type call(U &v)
	{
	  return std::get<I>(v);
	}
      };
    } // namespace traits
  } // namespace geometry
} // namespace particle
