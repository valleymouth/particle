// Kokkos headers
#include <Kokkos_Core.hpp>

// Boost headers
#include <boost/chrono.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/random.hpp>

// Std headers
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct input_params
{
  std::size_t particle_count;
  double neighbor_cutoff;
  double lower_x;
  double upper_x;
  double lower_y;
  double upper_y;
  double lower_z;
  double upper_z;
  double cell_size;
  std::size_t step_count;
  
  void load(const std::string &filename)
  {
    namespace pt = boost::property_tree;

    pt::ptree tree;
    pt::read_xml(filename, tree);
    particle_count = tree.get<std::size_t>("input.count");
    neighbor_cutoff = tree.get<double>("input.cutoff");
    lower_x = tree.get<double>("input.lower.x");
    lower_y = tree.get<double>("input.lower.y");
    lower_z = tree.get<double>("input.lower.z");
    upper_x = tree.get<double>("input.upper.x");
    upper_y = tree.get<double>("input.upper.y");
    upper_z = tree.get<double>("input.upper.z");
    cell_size = tree.get<double>("input.cell_size");
    step_count = tree.get<std::size_t>("input.step_count");
  }

  void save(const std::string &filename)
  {
    namespace pt = boost::property_tree;

    pt::ptree tree;
    tree.put("input.count", particle_count);
    tree.put("input.cutoff", neighbor_cutoff);
    tree.put("input.lower.x", lower_x);
    tree.put("input.lower.y", lower_y);
    tree.put("input.lower.z", lower_z);
    tree.put("input.upper.x", upper_x);
    tree.put("input.upper.y", upper_y);
    tree.put("input.upper.z", upper_z);
    tree.put("input.cell_size", cell_size);
    tree.put("input.step_count", step_count);
    pt::write_xml(filename, tree);
  }
};

template <class ForwardIterator>
void random_fill(ForwardIterator begin, ForwardIterator end, double lower, double upper)
{
  static boost::random::mt11213b rng;
  boost::random::uniform_real_distribution<> dist(lower, upper);
  std::generate(begin, end, [&]() { return dist(rng); });
}

double cell_distance(int i, int j, int k, double cell_size)
{
  double x = 0;
  if (i > 0) x = (i - 1) * cell_size;
  else if (i < 0) x = (i + 1) * cell_size;
  double y = 0;
  if (j > 0) y = (j - 1) * cell_size;
  else if (j < 0) y = (j + 1) * cell_size;
  double z = 0;
  if (k > 0) z = (k - 1) * cell_size;
  else if (k < 0) z = (k - 1) * cell_size;
  return std::sqrt(x * x + y * y + z * z);
}

int main(int argc, char **argv)
{
  namespace po = boost::program_options;
  
  Kokkos::ScopeGuard kokkos(argc, argv);

  std::string filename;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("touch", "produce empty input file")
    ("input,i", po::value<std::string>(&filename), "set input filename")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("touch"))
  {
    input_params ip;
    ip.save("input.xml");
    return 1;
  }

  if (vm.count("help") || filename.empty()) {
    std::cout << desc << std::endl;
    return 1;
  }
  
  input_params ip;
  ip.load(filename);
  
  size_t particle_count = ip.particle_count;
  double neighbor_cutoff = ip.neighbor_cutoff;
  const double lower_x = ip.lower_x - neighbor_cutoff;
  const double lower_y = ip.lower_y - neighbor_cutoff;
  const double lower_z = ip.lower_z - neighbor_cutoff;
  const double upper_x = ip.upper_x + neighbor_cutoff;
  const double upper_y = ip.upper_y + neighbor_cutoff;
  const double upper_z = ip.upper_z + neighbor_cutoff;
  const double cell_size = ip.cell_size;
  const int cell_count_x = std::ceil((upper_x - lower_x) / cell_size);
  const int cell_count_y = std::ceil((upper_y - lower_y) / cell_size);
  const int cell_count_z = std::ceil((upper_z - lower_z) / cell_size);
  const int max_cell_count = cell_count_x * cell_count_y * cell_count_z;

  const std::size_t step_count = ip.step_count;
  
  std::vector<double> x(particle_count);
  random_fill(x.begin(), x.end(), ip.lower_x, ip.upper_x);

  std::vector<double> y(particle_count);
  random_fill(y.begin(), y.end(), ip.lower_y, ip.upper_y);
  
  std::vector<double> z(particle_count);
  random_fill(z.begin(), z.end(), ip.lower_z, ip.upper_z);

  typedef Kokkos::View<
    double *
    , Kokkos::HostSpace
    , Kokkos::MemoryTraits<Kokkos::Unmanaged>
    > HostUnmanagedView;
  HostUnmanagedView h_x(x.data(), particle_count);
  HostUnmanagedView h_y(y.data(), particle_count);
  HostUnmanagedView h_z(z.data(), particle_count);

  Kokkos::View<double *> d_x("x", particle_count);
  Kokkos::View<double *> d_y("y", particle_count);
  Kokkos::View<double *> d_z("z", particle_count);

  Kokkos::deep_copy(d_x, h_x);
  Kokkos::deep_copy(d_y, h_y);
  Kokkos::deep_copy(d_z, h_z);

  Kokkos::View<double *> d_input0("input0", particle_count);
  Kokkos::View<double *> d_input1("input1", particle_count);
  Kokkos::View<double *> d_input2("input2", particle_count);
  Kokkos::View<double *> d_input3("input3", particle_count);
  Kokkos::View<double *> d_input4("input4", particle_count);
  Kokkos::View<double *> d_input5("input5", particle_count);

  Kokkos::View<double *> d_output0("output0", particle_count);
  Kokkos::View<double *> d_output1("output1", particle_count);
  Kokkos::View<double *> d_output2("output2", particle_count);

  const int cell_count = cell_count_x * cell_count_y * cell_count_z;
  int max_particle_per_cell = 8;
  
  Kokkos::View<int *> d_cell_indices("cell_indices", particle_count);
  Kokkos::View<int *> d_particle_per_cell("particle_per_cell", cell_count);
  Kokkos::View<int **> d_cell_particles("cell_particles", cell_count, max_particle_per_cell);  
  
  int stencil_count_x = std::ceil(neighbor_cutoff / cell_size);
  int stencil_count_y = std::ceil(neighbor_cutoff / cell_size);
  int stencil_count_z = std::ceil(neighbor_cutoff / cell_size);
  std::size_t max_stencil_count = (2 * stencil_count_x + 1)
    * (2 * stencil_count_y + 1)
    * (2 * stencil_count_z + 1);

  Kokkos::View<int *> d_stencil = Kokkos::View<int *>("stencil", max_stencil_count);
  auto h_stencil = Kokkos::create_mirror_view(d_stencil);
  int stencil_count = 0;
  for (int k = -stencil_count_z; k <= stencil_count_z; k++)
  {
    for (int j = -stencil_count_y; j <= stencil_count_y; j++)
    {
      for (int i = -stencil_count_x; i <= stencil_count_x; i++)
      {
        if (cell_distance(i, j, k, cell_size) < neighbor_cutoff)
          h_stencil(stencil_count++) = i + j * cell_count_x + k * cell_count_x * cell_count_y;
      }
    }
  }
  Kokkos::deep_copy(d_stencil, h_stencil);
  
  std::size_t max_neighbor_count = 16;
  Kokkos::View<int *> d_neighbor_count = Kokkos::View<int *>("neighbor_count", particle_count);
  Kokkos::View<int **> d_neighbors = Kokkos::View<int **>("neighbors", particle_count, max_neighbor_count);

  Kokkos::View<int> d_resize("resize");
  auto h_resize = Kokkos::create_mirror_view(d_resize);
  for (int step = 0; step < step_count; step++)
  {
    h_resize() = 1;
    while(h_resize())
    {
      h_resize() = 0;
      deep_copy(d_resize, h_resize);
      Kokkos::deep_copy(d_particle_per_cell, 0);
      Kokkos::Profiling::pushRegion("cell list");
      Kokkos::parallel_for("cell list", particle_count
			   , KOKKOS_LAMBDA(const int i)
                           {
                             int x = (d_x(i) - lower_x) / cell_size;
                             int y = (d_y(i) - lower_y) / cell_size;
                             int z = (d_z(i) - lower_z) / cell_size;
                             int cell = x + y * cell_count_x + z * cell_count_x * cell_count_y;
                             d_cell_indices(i) = cell;
                             int j = Kokkos::atomic_fetch_add(&d_particle_per_cell(cell), 1);
                             if (j < d_cell_particles.extent(1))
                               d_cell_particles(cell, j) = i;
                             else
                               d_resize() = 1;
                           });
      Kokkos::Profiling::popRegion();
      deep_copy(h_resize, d_resize);
      if(h_resize())
      {
	max_particle_per_cell *= 2;
	d_cell_particles = Kokkos::View<int **>("cell_particles", cell_count, max_particle_per_cell);
      }
    }

    h_resize() = 1;
    while(h_resize())
    {
      h_resize() = 0;
      Kokkos::deep_copy(d_resize, h_resize);
      Kokkos::deep_copy(d_neighbor_count, 0);
      Kokkos::Profiling::pushRegion("neighbor list");
      Kokkos::parallel_for("neighbor list", particle_count
			   , KOKKOS_LAMBDA(const int i)
                           {
                             double x = d_x(i);
                             double y = d_y(i);
                             double z = d_z(i);
                             int cell = d_cell_indices(i);
                             int count = 0;
                             for (int s = 0; s < stencil_count; s++)
                             {
                               int c = cell + d_stencil(s);
                               if (c >= 0 && c < max_cell_count)
                               {
                                 for (int p = 0; p < d_particle_per_cell(c); p++)
                                 {
                                   int j = d_cell_particles(c, p);
                                   double dx = d_x(j) - x;
                                   double dy = d_y(j) - y;
                                   double dz = d_z(j) - z;
                                   double d = sqrt(dx * dx + dy * dy + dz * dz);
                                   if (d < neighbor_cutoff && i != j)
                                   {
                                     if (count < max_neighbor_count - 1)
                                       d_neighbors(i, count++) = j;
                                     else
                                       d_resize() = 1;
                                   }
                                 }
                               }
                             }
                             d_neighbor_count(i) = count;
                           });
      Kokkos::Profiling::popRegion();
      Kokkos::deep_copy(h_resize, d_resize);
      if (h_resize())
      {
	max_neighbor_count *= 2;
	d_neighbors = Kokkos::View<int **>("neighbors", particle_count, max_neighbor_count);
      }
    }

    Kokkos::Profiling::pushRegion("pairwise interaction");
    Kokkos::parallel_for("pairwise interaction", particle_count
			 , KOKKOS_LAMBDA(const int i)
                         {
                           double result0 = 0;
                           double result1 = 0;
                           double result2 = 0;
                           double x = d_x(i);
                           double y = d_y(i);
                           double z = d_z(i);
                           for (int n = 0; n < d_neighbor_count(i); n++)
                           {
                             int j = d_neighbors(i, n);
                             double dx = d_x(n) - x;
                             double dy = d_y(n) - y;
                             double dz = d_z(n) - z;
                             double d = sqrt(dx * dx + dy * dy + dz * dz);
                             double var0 = d_input0(j) - d_input0(i);
                             double var1 = d_input1(j) - d_input1(i);
                             double var2 = d_input2(j) - d_input2(i);
                             result0 += var0 / d;
                             result1 += var1 / d;
                             result2 += var2 / d;
                           }
                           d_output0(i) = result0;
                           d_output1(i) = result1;
                           d_output2(i) = result2;
                         });
    Kokkos::Profiling::popRegion();
  }

  double neighbor_count_sum = 0;
  Kokkos::parallel_reduce(particle_count
                          , KOKKOS_LAMBDA(const int i, double &update)
                          {
                            update += d_neighbor_count(i);
                          }, neighbor_count_sum);
  double neighbor_count_average = neighbor_count_sum / particle_count;
  
  double neighbor_count_square_sum = 0;                            
  Kokkos::parallel_reduce(particle_count
                          , KOKKOS_LAMBDA(const int i, double &update)
                          {
                            int count = d_neighbor_count(i);
                            update += count * count;
                          }, neighbor_count_square_sum);
  double neighbor_count_variance = neighbor_count_square_sum / particle_count;

  std::cout << "# of neighbors: (" << neighbor_count_average << ", " << std::sqrt(neighbor_count_variance) << ")" << std::endl;

  /*
  Kokkos::deep_copy(h_x, d_x);
  Kokkos::deep_copy(h_y, d_y);
  Kokkos::deep_copy(h_z, d_z);

  std::cout << "stencil: ";
  for (int i = 0; i < stencil_count; i++)
  {
    std::cout << "(" << i << ": " << h_stencil(i) << ") ";
  }
  std::cout << std::endl;
  
  auto h_cell_indices = Kokkos::create_mirror_view(d_cell_indices);
  Kokkos::deep_copy(h_cell_indices, d_cell_indices);
  auto h_particle_per_cell = Kokkos::create_mirror_view(d_particle_per_cell);
  Kokkos::deep_copy(h_particle_per_cell, d_particle_per_cell);
  auto h_cell_particles = Kokkos::create_mirror_view(d_cell_particles);
  Kokkos::deep_copy(h_cell_particles, d_cell_particles);
  
  for (int i = 0; i < particle_count; i++)
    std::cout << i << ": (" << h_x(i) << ", " << h_y(i) << ", " << h_z(i) << ") -> " << h_cell_indices(i) << std::endl;
  for (int i = 0; i < cell_count; i++)
  {
    if (h_particle_per_cell(i))
    {
      std::cout << i << ": ";
      for (int j = 0; j < h_particle_per_cell(i); j++)
      {
	std::cout << "(" << j << ": " << h_cell_particles(i, j) << ") ";
      }
      std::cout << std::endl;
    }
  }

  auto h_neighbor_count = Kokkos::create_mirror_view(d_neighbor_count);
  auto h_neighbors = Kokkos::create_mirror_view(d_neighbors);
  Kokkos::deep_copy(h_neighbor_count, d_neighbor_count);
  Kokkos::deep_copy(h_neighbors, d_neighbors);
  for (int i = 0; i < particle_count; i++)
  {
    std::cout << i << ": ";
    for (int j = 0; j < h_neighbor_count(i); j++)
    {
      std::cout << "(" << j << ": " << h_neighbors(i, j) << ") ";
    }
    std::cout << std::endl;
  }
  */
  
  return 0;
}
