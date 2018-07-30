#pragma once

// Boost headers
#include <boost/type_traits/remove_const.hpp>

namespace particle
{
  namespace geometry
  {
    struct untagged;

    namespace traits
    {
      template <class>
      struct tag
      {
	typedef untagged type;
      };
    }

    template<class T>
    struct tag
      : traits::tag<typename boost::remove_const<T>::type>
    {};
  } // namespace geometry
} // namespace particle
