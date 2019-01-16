#pragma once

// Std headers
#include <cmath>

namespace particle
{
namespace mps
{
  namespace detail
  {
    template <int Dimension>
    struct pnd0;

    template <>
    struct pnd0<2>
    {
      template <class T, class Kernel>
      static T call(T dbp, T re, Kernel k)
      {
        T ret = 0;
        int n = static_cast<int>(std::ceil(re / dbp));
        for (T x = -dbp * n; x < re; x += dbp)
        {
          for (T y = -dbp * n; y < re; y += dbp)
          {
            T r = std::sqrt(x * x + y * y);
            if (r > dbp / 2) // make sure that we don't compute for x = y = 0
            {
              ret += k(r);
            }
          }
        }
        return ret;
      }
    };

    template <>
    struct pnd0<3>
    {
      template <class T, class Kernel>
      static T call(T dbp, T re, Kernel k)
      {
        T ret = 0;
        int n = static_cast<int>(std::ceil(re / dbp));
        for (T x = -dbp * n; x < re; x += dbp)
        {
          for (T y = -dbp * n; y < re; y += dbp)
          {
            for (T z = -dbp * n; z < re; z += dbp)
            {
              T r = std::sqrt(x * x + y * y + z * z);
              if (r > dbp / 2) // make sure that we don't compute for x = y = z = 0
              {
                ret += k(r);
              }
            }
          }
        }
        return ret;
      }
    };
  } // namespace detail

  template <int Dimension, class T, class Kernel>
  T pnd0(T dbp, T re, Kernel k)
  {
    return detail::pnd0<Dimension>::call(dbp, re, k);
  }
} // namespace mps
} // namespace particle
