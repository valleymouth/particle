// Kokkos headers
#include <Kokkos_Core.hpp>

// Boost headers
#include <boost/chrono.hpp>
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

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cerr << "Usage: coalesced_bench SIZE" << std::endl;
    return 1;
  }

  Kokkos::ScopeGuard kokkos(argc, argv);
    
  const std::size_t n = std::stoi(argv[1]);

  Kokkos::View<double *> x0("x0", n);
  Kokkos::View<double *> y0("y0", n);
  Kokkos::View<double *> z0("z0", n);
  Kokkos::View<double *> x1("x1", n);
  Kokkos::View<double *> y1("y1", n);
  Kokkos::View<double *> z1("z1", n);

  Kokkos::View<double *> v0("v0", 3 * n);
  Kokkos::View<double *> v1("v1", 3 * n);

  Kokkos::View<double *> d0("d0", n);
  Kokkos::View<double *> d1("d1", n);
  
  random_fill(x0, -1.0, 1.0);
  random_fill(y0, -1.0, 1.0);
  random_fill(z0, -1.0, 1.0);
  random_fill(x1, -1.0, 1.0);
  random_fill(y1, -1.0, 1.0);
  random_fill(z1, -1.0, 1.0);

  Kokkos::parallel_for(
    n,
    KOKKOS_LAMBDA(const int i)
    {
      v0(3 * i + 0) = x0(i);
      v0(3 * i + 1) = y0(i);
      v0(3 * i + 2) = z0(i);
      v1(3 * i + 0) = x1(i);
      v1(3 * i + 1) = y1(i);
      v1(3 * i + 2) = z1(i);
    });
  Kokkos::fence();
  
  using clock = boost::chrono::high_resolution_clock;

  clock::time_point tp0 = clock::now();

  Kokkos::parallel_for(
    n,
    KOKKOS_LAMBDA(const int i)
    {
      double dx = x1(i) - x0(i);
      double dy = y1(i) - y0(i);
      double dz = z1(i) - z0(i);
      d0(i) = sqrt(dx * dx + dy * dy + dz * dz);
    });
  Kokkos::fence();
  
  auto duration0 = clock::now() - tp0;
  
  clock::time_point tp1 = clock::now();
  
  Kokkos::parallel_for(
    n,
    KOKKOS_LAMBDA(const int i)
    {
      double dx = v1(3 * i + 0) - v0(3 * i + 0);
      double dy = v1(3 * i + 1) - v0(3 * i + 1);
      double dz = v1(3 * i + 2) - v0(3 * i + 2);
      d1(i) = sqrt(dx * dx + dy * dy + dz * dz);
    });
  Kokkos::fence();

  auto duration1 = clock::now() - tp1;
  
  std::cout << "coalesced: " << duration0.count() << " uncoalesced: " << duration1.count() << std::endl;
  
  return 0;
}
