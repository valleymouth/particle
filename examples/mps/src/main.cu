// Particle headers
#include <particle/collection.hpp>
#include <particle/geometry/adapted/cuda/float2.hpp>
#include <particle/geometry/adapted/cuda/int2.hpp>
#include <particle/geometry/adapted/cuda/thrust_tuple.hpp>
#include <particle/geometry/adapted/cuda/thrust_zip_iterator.hpp>
#include <particle/geometry/box.hpp>
#include <particle/grid/left_grid.hpp>
#include <particle/io/vtk.hpp>
#include <particle/neighbour/cell_list.hpp>

// Thrust headers
#include <thrust/device_vector.h>
#include <thrust/for_each.h>
#include <thrust/host_vector.h>

// Boost headers
#include <boost/chrono.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/random.hpp>

// Std headers
#include <iostream>
#include <vector>

struct input_params
{
  std::size_t particle_count;
  float cutoff;
  float lower_x;
  float upper_x;
  float lower_y;
  float upper_y;
  float lower_z;
  float upper_z;
  float cell_size;
  std::size_t step_count;
  
  void load(const std::string &filename)
  {
    namespace pt = boost::property_tree;

    pt::ptree tree;
    pt::read_xml(filename, tree);
    particle_count = tree.get<std::size_t>("input.count");
    cutoff = tree.get<float>("input.cutoff");
    lower_x = tree.get<float>("input.lower.x");
    lower_y = tree.get<float>("input.lower.y");
    lower_z = tree.get<float>("input.lower.z");
    upper_x = tree.get<float>("input.upper.x");
    upper_y = tree.get<float>("input.upper.y");
    upper_z = tree.get<float>("input.upper.z");
    cell_size = tree.get<float>("input.cell_size");
    step_count = tree.get<std::size_t>("input.step_count");
  }

  void save(const std::string &filename)
  {
    namespace pt = boost::property_tree;

    pt::ptree tree;
    tree.put("input.count", particle_count);
    tree.put("input.cutoff", cutoff);
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

struct id_;
struct type_;
struct x_;
struct y_;
struct vx_;
struct vy_;

using position_ = boost::mpl::vector<x_, y_>;
using velocity_ = boost::mpl::vector<vx_, vy_>;

int main(int argc, char** argv)
{
  namespace po = boost::program_options;
  
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
  
  using boost::fusion::pair;
  particle::collection<
    pair<id_, thrust::device_vector<int>>
    , pair<type_, thrust::device_vector<int>>
    , pair<x_, thrust::device_vector<float>>
    , pair<y_, thrust::device_vector<float>>> col;
  col.resize(ip.particle_count);

  thrust::host_vector<float> x(ip.particle_count);
  random_fill(x.begin(), x.end(), ip.lower_x, ip.upper_x);

  thrust::host_vector<float> y(ip.particle_count);
  random_fill(y.begin(), y.end(), ip.lower_y, ip.upper_y);

  thrust::host_vector<int> id(ip.particle_count);
  thrust::host_vector<int> type(ip.particle_count);
  for (int i = 0; i < ip.particle_count; i++)
  {
    id[i] = i;
    type[i] = 2 * i / ip.particle_count;
  }

  thrust::copy(id.begin(), id.end(), col.begin<id_>());
  thrust::copy(type.begin(), type.end(), col.begin<type_>());
  thrust::copy(x.begin(), x.end(), col.begin<x_>());
  thrust::copy(y.begin(), y.end(), col.begin<y_>());
  
  thrust::for_each(col.begin(), col.end(),
                   PARTICLE_LAMBDA (const thrust::tuple<int, int, float, float>& x)
                   { printf("%d %d %f %f\n", thrust::get<0>(x), thrust::get<1>(x), thrust::get<2>(x), thrust::get<3>(x)); });

  using box_type = particle::geometry::box<int2, int2>;

  auto grid = particle::left_grid<box_type, float>(
    box_type(
      make_int2(std::floor(ip.lower_x / ip.cell_size) - 1,
                std::floor(ip.lower_y / ip.cell_size) - 1)
      , make_int2(std::ceil(ip.upper_x / ip.cell_size) + 1,
                  std::ceil(ip.upper_y / ip.cell_size) + 1))
    , ip.cell_size);

  particle::neighbour::cell_list<decltype(grid)> cl(grid);
  cl.build(col.begin<position_>(), col.end<position_>(), col.begin());

  thrust::for_each(col.begin(), col.end(),
                   PARTICLE_LAMBDA (const thrust::tuple<int, int, float, float>& x)
                   { printf("%d %d %f %f\n", thrust::get<0>(x), thrust::get<1>(x), thrust::get<2>(x), thrust::get<3>(x)); });

  cl.pair_interact(
    col.begin<position_>()
    , col.end<position_>()
    , PARTICLE_LAMBDA(int i, int j)
    { if (i != j) printf("%d %d\n", i, j); });
  
  particle::collection<
    pair<id_, thrust::host_vector<int>>
    , pair<type_, thrust::host_vector<int>>
    , pair<x_, thrust::host_vector<float>>
    , pair<y_, thrust::host_vector<float>>> col_host;
  col_host.resize(ip.particle_count);
  thrust::copy(col.begin(), col.end(), col_host.begin());

  particle::io::vtk::save(
    "test.vtu"
    , col_host.begin<position_>()
    , col_host.end<position_>()
    , boost::fusion::make_vector("id", "type")
    , boost::fusion::make_vector(col_host.begin<id_>(), col_host.begin<type_>())); 

  return 0;
}
