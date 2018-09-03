// Kokkos headers
#include <Kokkos_Core.hpp>

// Boost headers
#include <boost/chrono.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/array.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_fused.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/random.hpp>

// Std headers
#include <iostream>
#include <string>

template <class ForwardIterator>
void random_fill(ForwardIterator begin, ForwardIterator end, double lower, double upper)
{
  static boost::random::mt11213b rng;
  boost::random::uniform_real_distribution<> dist(lower, upper);
  std::generate(begin, end, [&]() { return dist(rng); });
}

template <class View>
void random_fill(View view, double lower, double upper)
{
  const std::size_t n = view.extent(0);
  std::vector<double> values(n);
  random_fill(values.begin(), values.end(), -1.0, 1.0);

  typedef Kokkos::View<
    double *
    , Kokkos::HostSpace
    , Kokkos::MemoryTraits<Kokkos::Unmanaged>
    > HostUnmanagedView;
  HostUnmanagedView h_view(values.data(), n);

  Kokkos::deep_copy(view, h_view);
}

BOOST_FUSION_ADAPT_STRUCT(float3, (float, x)(float, y)(float, z))

namespace detail
{
  struct minus
  {
    template <class> struct result;
  
    template <class F, class T>
    struct result<F(T, T)>
    {
      typedef T type;
    };

    template <class T>
    __host__ __device__ T operator()(const T& x0, const T& x1) const
    {
      return x0 - x1;
    }
  };
}

template <class T0, class T1>
__host__ __device__ auto minus(const T0& x0, const T1& x1) -> decltype(boost::fusion::transform(x0, x1, detail::minus()))
{
  return boost::fusion::transform(x0, x1, detail::minus());
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cerr << "Usage: fusion_bench SIZE" << std::endl;
    return 1;
  }

  Kokkos::ScopeGuard kokkos(argc, argv);

  const std::size_t n = std::stoi(argv[1]);

  Kokkos::View<double *> x0("x", n);
  Kokkos::View<double *> y0("y", n);
  Kokkos::View<double *> z0("z", n);
  Kokkos::View<double *> x1("x", n);
  Kokkos::View<double *> y1("y", n);
  Kokkos::View<double *> z1("z", n);
  Kokkos::View<double *> d("d", n);
  
  random_fill(x0, -1.0, 1.0);
  random_fill(y0, -1.0, 1.0);
  random_fill(z0, -1.0, 1.0);
  random_fill(x1, -1.0, 1.0);
  random_fill(y1, -1.0, 1.0);
  random_fill(z1, -1.0, 1.0);

  using clock = boost::chrono::high_resolution_clock;
  auto tp0 = clock::now();

  Kokkos::parallel_for(
    n,
    KOKKOS_LAMBDA(const int i)
    {
      double dx = x1(i) - x0(i);
      double dy = y1(i) - y0(i);
      double dz = z1(i) - z0(i);
      d(i) = sqrt(dx * dx + dy * dy + dz * dz);
    });

  Kokkos::fence();
  auto duration0 = clock::now() - tp0;
  auto tp1 = clock::now();
  
  Kokkos::parallel_for(
    n,
    KOKKOS_LAMBDA(const int i)
    {
      using boost::fusion::at_c;
      float3 f0 = make_float3(x0(i), y0(i), z0(i));
      float3 f1 = make_float3(x1(i), y1(i), z1(i));
      auto v = minus(f1, f0);
      d(i) = sqrt(at_c<0>(v) * at_c<0>(v) + at_c<1>(v) * at_c<1>(v) + at_c<2>(v) * at_c<2>(v));
    });

  Kokkos::fence();
  auto duration1 = clock::now() - tp1;

  std::cout << "unfused: " << duration0.count() << " fused: " << duration1.count() << std::endl;

  return 0;
}
