#pragma once

// Local headers
#include "tags.hpp"

// Boost headers
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace particle
{
  namespace geometry
  {
    struct untagged;

    namespace traits
    {
      template <class T>
      struct tag
      {
        typedef typename boost::mpl::if_<
          boost::fusion::traits::is_sequence<T>
          , tags::vector_tag // boost fusion sequences are vectors
          , untagged>::type type;
      };
    }

    template<class T>
    struct tag
      : traits::tag<typename boost::remove_const<T>::type>
    {};
  } // namespace geometry
} // namespace particle
