#pragma once

// Local headers
#include "tag_of.hpp"

// Particle headers
#include "../config.hpp"

namespace particle
{
  namespace geometry
  {
    namespace extension
    {
      template <class>
      struct zero_impl;
    }
    
    namespace result_of
    {
      template <class T>
      struct zero
	: extension::zero_impl<
        typename detail::tag_of<T>::type
	>::template apply<T>
      {};
    }

    template <class T>
    PARTICLE_HOST_AND_DEVICE
    inline typename result_of::zero<T>::type zero()
    {
      return result_of::zero<T>::call();
    }
  } // namespace geometry
} // namespace particle
