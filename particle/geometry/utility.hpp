#pragma once

namespace particle
{
namespace geometry
{
  template <typename T, typename U>
  struct mem_fwd
  {
    using type = typename std::conditional<
      std::is_lvalue_reference<T>::value
      , typename std::conditional<
          std::is_const<
            typename std::remove_reference<T>::type>::value
          , U const&
          , U&>::type
      , U>::type;
  };
} // namespace geometry
} // namespace particle
