#pragma once

// Local headers
#include "../config.hpp"
#include "tag.hpp"

namespace particle
{
  namespace geometry
  {
    namespace traits
    {
      template <class, std::size_t, class>
      struct elem;
    }
    
    template <std::size_t N, class T>
    PARTICLE_INLINE_FUNCTION
    typename traits::elem<
      typename boost::remove_const<T>::type, N, T>::type elem(T &x)
    {
      return traits::elem<
	typename boost::remove_const<T>::type, N, T>::call(x);
    }
  } // namespace geometry
} // namespace particle
