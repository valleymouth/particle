#pragma once

// Std headers
#include <cmath>

namespace particle
{
namespace mps
{
  namespace detail
  {
    template <int>
    struct lambda;

    template <>
    struct lambda<2>
    {
      template <class T, class Kernel>
      static T call(T dbp, T re, T pnd0, Kernel k)
      {
        T ret = 0;
        int n = static_cast<int>(std::ceil(re / dbp));
        for (T x = -dbp * n; x < re; x += dbp)
        {
          for (T y = -dbp * n; y < re; y += dbp)
          {
            T r2 = x * x + y * y;
            T r = std::sqrt(r2);
            if (r > dbp / 2) // make sure that we don't compute for x = y = 0
            {
              ret += k(r) * r2;
            }
          }
        }
        ret /= pnd0;
        return ret;
      }
    };

    template <>
    struct lambda<3>
    {
      template <class T, class Kernel>
      static T call(T dbp, T re, T pnd0, Kernel k)
      {
        T ret = 0;
        int n = static_cast<int>(std::ceil(re / dbp));
        for (T x = -dbp * n; x < re; x += dbp)
        {
          for (T y = -dbp * n; y < re; y += dbp)
          {
            for (T z = -dbp * n; z < re; z += dbp)
            {
              T r2 = x * x + y * y + z * z;
              T r = std::sqrt(r2);
              if (r > dbp / 2) // make sure that we don't compute for x = y = z = 0
              {
                ret += k(r) * r2;
              }
            }
          }
        }
        ret /= pnd0;
        return ret;
      }
    };
  } // namespace detail

  template <int Dimension, class T, class Kernel>
  T lambda(T dbp, T re, T pnd0, Kernel k)
  {
    return detail::lambda<Dimension>::call(dbp, re, pnd0, k);
  }
} // namespace mps
} // namespace particle
