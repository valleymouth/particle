// Particle headers
#include <particle/collection.hpp>
#include <particle/geometry/adapted/cuda/double2.hpp>
#include <particle/geometry/adapted/cuda/int2.hpp>
#include <particle/geometry/adapted/cuda/thrust_tuple.hpp>
#include <particle/geometry/adapted/cuda/thrust_zip_iterator.hpp>
#include <particle/geometry/as.hpp>
#include <particle/geometry/box.hpp>
#include <particle/geometry/distance.hpp>
#include <particle/geometry/elem.hpp>
#include <particle/geometry/length.hpp>
#include <particle/geometry/operators.hpp>
#include <particle/grid/left_grid.hpp>
#include <particle/io/vtk.hpp>
#include <particle/mps/kernels.hpp>
#include <particle/mps/lambda.hpp>
#include <particle/mps/pnd0.hpp>
#include <particle/neighbour/cell_list.hpp>

// Thrust headers
#include <thrust/device_vector.h>
#include <thrust/for_each.h>
#include <thrust/host_vector.h>

// Boost headers
#include <boost/chrono.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/random.hpp>

// Std headers
#include <iostream>
#include <vector>

enum class category_t {fluid, solid, ghost, unknown};
enum class motion_t {free, fixed, imposed, unknown};

struct input_params
{
  struct type
  {
    std::string name;
    category_t category;
    motion_t motion;
    float density;
    float viscosity;
  };

  struct box
  {
    std::string type;
    float origin[3];
    int size[3];

    box(): origin{0, 0, 0}, size{0, 0, 0} {}
  };

  float time_step;
  float distance_between_particles;
  float cutoff;
  float gravity;
  float speed_of_sound;
  float free_surface_threshold;
  float free_surface_pressure;
  float lower[3];
  float upper[3];
  float cell_size;
  std::size_t step_count;
  std::size_t steps_per_output;
  std::map<std::string, type> types;
  std::vector<box> boxes;
  std::string output_filename;
  
  input_params()
    : time_step(1)
    , distance_between_particles(0)
    , cutoff(0)
    , gravity(0)
    , speed_of_sound(0)
    , free_surface_threshold(0)
    , free_surface_pressure(0)
    , lower{0, 0, 0}
    , upper{0, 0, 0}
    , cell_size(0)
    , step_count(0)
    , steps_per_output(1)
  {}
  
  void load(const std::string &filename)
  {
    namespace pt = boost::property_tree;

    pt::ptree tree;
#pragma push
#pragma diag_suppress = code_is_unreachable
#pragma diag_suppress = initialization_not_reachable
    pt::read_xml(filename, tree, pt::xml_parser::trim_whitespace);
#pragma pop
    time_step = tree.get<float>("input.time_step");
    distance_between_particles = tree.get<float>("input.distance_between_particles");
    cutoff = tree.get<float>("input.cutoff");
    gravity = tree.get<float>("input.gravity");
    speed_of_sound = tree.get<float>("input.speed_of_sound");
    free_surface_threshold = tree.get<float>("input.free_surface_threshold");
    free_surface_pressure = tree.get<float>("input.free_surface_pressure");
    lower[0] = tree.get<float>("input.lower.x");
    lower[1] = tree.get<float>("input.lower.y");
    lower[2]= tree.get<float>("input.lower.z");
    upper[0] = tree.get<float>("input.upper.x");
    upper[1]= tree.get<float>("input.upper.y");
    upper[2] = tree.get<float>("input.upper.z");
    cell_size = tree.get<float>("input.cell_size");
    step_count = tree.get<std::size_t>("input.step_count");
    steps_per_output = tree.get<std::size_t>("input.steps_per_output");
    BOOST_FOREACH (auto& c, tree.get_child("input").equal_range("type"))
    {
      type t;
      t.name = c.second.get<std::string>("name");
      std::string category = c.second.get<std::string>("category");
      if (category == "fluid")
        t.category = category_t::fluid;
      else if (category == "solid")
        t.category = category_t::solid;
      else if (category == "ghost")
        t.category = category_t::ghost;
      else
        t.category = category_t::unknown;
      std::string motion = c.second.get<std::string>("motion");
      if (motion == "free")
        t.motion = motion_t::free;
      else if (motion == "fixed")
        t.motion = motion_t::fixed;
      else if (motion == "imposed")
        t.motion = motion_t::imposed;
      else
        t.motion = motion_t::unknown;
      t.density = c.second.get<float>("density");
      t.viscosity = c.second.get<float>("viscosity");
      types.insert({t.name, t});
    }
    try
    {
      BOOST_FOREACH (auto& c, tree.get_child("input").equal_range("box"))
      {
        box b;
        b.type = c.second.get<std::string>("type");
        b.origin[0] = c.second.get<float>("origin_x");
        b.origin[1] = c.second.get<float>("origin_y");
        b.origin[2] = c.second.get<float>("origin_z");
        b.size[0] = c.second.get<int>("size_x");
        b.size[1] = c.second.get<int>("size_y");
        b.size[2] = c.second.get<int>("size_z");
        boxes.push_back(b);
      }
    }
    catch(...) {} // no boxes on input file
    output_filename = tree.get<std::string>("input.output_filename");
  }
};

template <class ForwardIterator>
void random_fill(ForwardIterator begin, ForwardIterator end, double lower, double upper)
{
  static boost::random::mt11213b rng;
  boost::random::uniform_real_distribution<> dist(lower, upper);
  std::generate(begin, end, [&]() { return dist(rng); });
}

namespace tag
{
  struct id;
  struct type;
  struct x;
  struct y;
  struct vx;
  struct vy;
  struct ax;
  struct ay;
  struct pnd;
  struct pressure;
  struct pressure_grad_x;
  struct pressure_grad_y;
  struct pred_x;
  struct pred_y;
  struct pred_vx;
  struct pred_vy;
  
  using position = boost::mpl::vector<x, y>;
  using velocity = boost::mpl::vector<vx, vy>;
  using acceleration = boost::mpl::vector<ax, ay>;
  using pressure_grad = boost::mpl::vector<pressure_grad_x, pressure_grad_y>;
  using pred_position = boost::mpl::vector<pred_x, pred_y>;
  using pred_velocity = boost::mpl::vector<pred_vx, pred_vy>;
}

const int max_types = 10;
__constant__ int categories[max_types];
__constant__ int motions[max_types];
__constant__ double densities[max_types];
__constant__ double viscosities[max_types];

int main(int argc, char** argv)
{
  namespace po = boost::program_options;
  using particle::geometry::operators::operator+;
  using particle::geometry::operators::operator-;
  using particle::geometry::operators::operator*;
  using particle::geometry::operators::operator/;
  
  std::string filename;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("input,i", po::value<std::string>(&filename), "set input filename")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help") || filename.empty()) {
    std::cout << desc << std::endl;
    return 0;
  }
  
  input_params ip;
  ip.load(filename);

  // Generate boxes
  thrust::host_vector<int> id;
  thrust::host_vector<int> type;
  thrust::host_vector<double> x;
  thrust::host_vector<double> y;
  int particle_count = 0;
  for (auto &b : ip.boxes)
  {
    int t = std::distance(ip.types.begin(), ip.types.find(b.type));
    double2 origin = make_double2(b.origin[0], b.origin[1]);
    for (int j = 0; j < b.size[1]; j++)
    {
      for (int i = 0; i < b.size[0]; i++)
      {
        id.push_back(particle_count++);
        type.push_back(t);
        auto p = origin + ip.distance_between_particles * make_double2(i, j);
        x.push_back(particle::geometry::elem<0>(p));
        y.push_back(particle::geometry::elem<1>(p));
      }
    }
  }

  using boost::fusion::pair;
  particle::collection<
    pair<tag::id, thrust::device_vector<int>>
    , pair<tag::type, thrust::device_vector<int>>
    , pair<tag::x, thrust::device_vector<double>>
    , pair<tag::y, thrust::device_vector<double>>
    , pair<tag::vx, thrust::device_vector<double>>
    , pair<tag::vy, thrust::device_vector<double>>
    , pair<tag::ax, thrust::device_vector<double>>
    , pair<tag::ay, thrust::device_vector<double>>
    , pair<tag::pnd, thrust::device_vector<double>>
    , pair<tag::pressure, thrust::device_vector<double>>
    , pair<tag::pressure_grad_x, thrust::device_vector<double>>
    , pair<tag::pressure_grad_y, thrust::device_vector<double>>
    , pair<tag::pred_x, thrust::device_vector<double>>
    , pair<tag::pred_y, thrust::device_vector<double>>
    , pair<tag::pred_vx, thrust::device_vector<double>>
    , pair<tag::pred_vy, thrust::device_vector<double>>
    > col;
  col.resize(particle_count);

  particle::collection<
    pair<tag::id, thrust::host_vector<int>>
    , pair<tag::type, thrust::host_vector<int>>
    , pair<tag::x, thrust::host_vector<double>>
    , pair<tag::y, thrust::host_vector<double>>
    , pair<tag::vx, thrust::host_vector<double>>
    , pair<tag::vy, thrust::host_vector<double>>
    , pair<tag::pnd, thrust::host_vector<double>>
    , pair<tag::pressure, thrust::host_vector<double>>
    > h_col;
  h_col.resize(particle_count);
  
  thrust::copy(id.begin(), id.end(), col.begin<tag::id>());
  thrust::copy(type.begin(), type.end(), col.begin<tag::type>());
  thrust::copy(x.begin(), x.end(), col.begin<tag::x>());
  thrust::copy(y.begin(), y.end(), col.begin<tag::y>());
  thrust::fill(
    col.begin<tag::velocity>()
    , col.end<tag::velocity>()
    , thrust::make_tuple(0.0, 0.0));
  thrust::fill(col.begin<tag::pnd>(), col.end<tag::pnd>(), 0);
  thrust::fill(col.begin<tag::pressure>(), col.end<tag::pressure>(), 0);
  
  using box_type = particle::geometry::box<int2, int2>;
  auto grid = particle::left_grid<box_type, double>(
    box_type(
      make_int2(std::floor(ip.lower[0] / ip.cell_size) - 1,
                std::floor(ip.lower[1] / ip.cell_size) - 1)
      , make_int2(std::ceil(ip.upper[0] / ip.cell_size) + 1,
                  std::ceil(ip.upper[1] / ip.cell_size) + 1))
    , ip.cell_size);

  using cell_list = particle::neighbour::cell_list<decltype(grid)>;
  cell_list cl(grid);

  const int dimensions = 2;
  const auto kernel = particle::mps::rational_kernel<double>(ip.cutoff);
  const double dbp = ip.distance_between_particles;
  const double pnd0 = particle::mps::pnd0<2>(dbp, static_cast<double>(ip.cutoff), kernel);
  const double lambda = particle::mps::lambda<2>(dbp, static_cast<double>(ip.cutoff), pnd0, kernel);

  const double laplacian_constant = 2 * dimensions / (lambda * pnd0);
  const double gradient_constant = dimensions / pnd0;

  int h_categories[max_types];
  std::transform(
    ip.types.begin()
    , ip.types.end()
    , h_categories
    , [](auto t) { return static_cast<int>(t.second.category); });
  cudaMemcpyToSymbol(categories, h_categories, ip.types.size() * sizeof(int));

  int h_motions[max_types];
  std::transform(
    ip.types.begin()
    , ip.types.end()
    , h_motions
    , [](auto t) { return static_cast<int>(t.second.motion); });
  cudaMemcpyToSymbol(motions, h_motions, ip.types.size() * sizeof(int));

  double h_densities[max_types];
  std::transform(
    ip.types.begin()
    , ip.types.end()
    , h_densities
    , [](auto t) { return t.second.density; });
  cudaMemcpyToSymbol(densities, h_densities, ip.types.size() * sizeof(double));

  double h_viscosities[max_types];
  std::transform(
    ip.types.begin()
    , ip.types.end()
    , h_viscosities
    , [](auto t) { return t.second.viscosity; });
  cudaMemcpyToSymbol(viscosities, h_viscosities, ip.types.size() * sizeof(double));

  using output_tags = boost::mpl::vector<tag::id, tag::type, tag::x, tag::y, tag::vx, tag::vy, tag::pnd, tag::pressure>;

  {
    thrust::copy(col.begin<output_tags>(), col.end<output_tags>(), h_col.begin<output_tags>());    std::stringstream ss;
    ss << ip.output_filename << "_0.vtu";
    particle::io::vtk::save(
      ss.str()
      , h_col.begin<tag::position>()
      , h_col.end<tag::position>()
      , boost::fusion::make_vector("id", "type", "pnd", "pressure", "velocity")
      , boost::fusion::make_vector(
        h_col.begin<tag::id>()
        , h_col.begin<tag::type>()
        , h_col.begin<tag::pnd>()
        , h_col.begin<tag::pressure>()
        , h_col.begin<tag::velocity>()));
  }

  // Simulation loop
  for (int step = 0; step < ip.step_count; step++)
  {
    cl.build(
      col.begin<tag::position>()
      , col.end<tag::position>()
      , col.begin<boost::mpl::vector<
      tag::id, tag::type, tag::x, tag::y, tag::vx, tag::vy>>());

    double gravity = ip.gravity;
    thrust::transform(
      col.begin<tag::type>()
      , col.end<tag::type>()
      , col.begin<tag::acceleration>()
      , PARTICLE_LAMBDA_DEVICE(int t)
      {
        if (motions[t] == static_cast<int>(motion_t::free))
          return thrust::make_tuple(0.0, -gravity);
        return thrust::make_tuple(0.0, 0.0);
      });

    auto type_first = col.begin<tag::type>();
    auto position_first = col.begin<tag::position>();
    auto velocity_first = col.begin<tag::velocity>();
    auto acceleration_first = col.begin<tag::acceleration>();
    cl.pair_interact(
      col.begin<tag::position>()
      , col.end<tag::position>()
      , PARTICLE_LAMBDA_DEVICE(int i, cell_list::neighbour_list nl)
      {
        using particle::geometry::as;
        int type_i = *(type_first + i);
        if (categories[type_i] != static_cast<int>(category_t::fluid))
          return;
        auto pos_i = *(position_first + i);
        auto vel_i = *(velocity_first + i);
        auto acc_i = *(acceleration_first + i);
        *(acceleration_first + i) =
          as<thrust::tuple<double, double>>(
            laplacian_constant * viscosities[type_i] * nl.reduce(
              i
              , pos_i
              , as<thrust::tuple<double, double>>(acc_i)
              , PARTICLE_LAMBDA_DEVICE(int i, int j, thrust::tuple<double, double>& value)
              {
                int type_j = *(type_first + j);
                if (categories[type_j] == static_cast<int>(category_t::ghost))
                  return;
                auto pos_j = *(position_first + j);
                auto vel_j = *(velocity_first + j);
                double r = particle::geometry::distance(pos_i, pos_j);
                value = as<thrust::tuple<double, double>>(
                  value + (vel_j - vel_i) * kernel(r));
              }));
      });

    double dt = ip.time_step;
    thrust::transform(
      col.begin<tag::velocity>()
      , col.end<tag::velocity>()
      , col.begin<tag::acceleration>()
      , col.begin<tag::pred_velocity>()
      , PARTICLE_LAMBDA(
        const thrust::tuple<double, double>& vel
        , const thrust::tuple<double, double>& acc)
      {
        return particle::geometry::as<thrust::tuple<double, double>>(vel + acc * dt);
      });

    thrust::transform(
      col.begin<tag::position>()
      , col.end<tag::position>()
      , col.begin<tag::pred_velocity>()
      , col.begin<tag::pred_position>()
      , PARTICLE_LAMBDA(
        const thrust::tuple<double, double>& pos
        ,const thrust::tuple<double, double>& vel)
      {
        return particle::geometry::as<thrust::tuple<double, double>>(pos + vel * dt);
      });

    cl.build(
      col.begin<tag::pred_position>()
      , col.end<tag::pred_position>()
      , col.begin<boost::mpl::vector<
      tag::id, tag::type, tag::pred_x, tag::pred_y, tag::pred_vx, tag::pred_vy>>());

    thrust::fill(col.begin<tag::pnd>(), col.end<tag::pnd>(), 0.0f);
    auto pnd_first = col.begin<tag::pnd>();
    auto pred_position_first = col.begin<tag::pred_position>();
    cl.pair_interact(
      col.begin<tag::pred_position>()
      , col.end<tag::pred_position>()
      , PARTICLE_LAMBDA_DEVICE(int i, cell_list::neighbour_list nl)
      {
        using particle::geometry::as;
        auto pos_i = *(pred_position_first + i);
        *(pnd_first + i) = nl.reduce(
          i
          , pos_i
          , 0.0
          , PARTICLE_LAMBDA_DEVICE(int i, int j, double& value)
          {
            auto pos_j = *(pred_position_first + j);
            double r = particle::geometry::distance(pos_i, pos_j);
            value = value + kernel(r);
          });
      });
    
    double c0 = ip.speed_of_sound;
    thrust::transform(
      col.begin<tag::pnd>()
      , col.end<tag::pnd>()
      , col.begin<tag::type>()
      , col.begin<tag::pressure>()
      , PARTICLE_LAMBDA_DEVICE(double pnd, int t)
      {
        if (categories[t] == static_cast<int>(category_t::ghost))
          return 0.0;
        return max(0.0, c0 * c0 * densities[t] * (pnd / pnd0 - 1)); 
      });

    double fst = ip.free_surface_threshold;
    double fsp = ip.free_surface_pressure;
    thrust::replace_if(
      col.begin<tag::pressure>()
      , col.end<tag::pressure>()
      , col.begin<tag::pnd>()
      , PARTICLE_LAMBDA(double pnd)
      {
        if (pnd < pnd0 * fst)
          return true;
        return false;
      }
      , fsp);

    thrust::fill(
      col.begin<tag::pressure_grad>()
      , col.end<tag::pressure_grad>()
      , thrust::make_tuple(0.0, 0.0));
    auto pressure_first = col.begin<tag::pressure>();
    auto pressure_grad_first = col.begin<tag::pressure_grad>();
    cl.pair_interact(
      col.begin<tag::pred_position>()
      , col.end<tag::pred_position>()
      , PARTICLE_LAMBDA_DEVICE(int i, cell_list::neighbour_list nl)
      {
        using particle::geometry::as;
        int type_i = *(type_first + i);
        if (categories[type_i] != static_cast<int>(category_t::fluid))
          return;
        auto pressure_i = *(pressure_first + i);
        auto pos_i = *(pred_position_first + i);
        *(pressure_grad_first + i) =
          as<thrust::tuple<double, double>>(
            gradient_constant / densities[type_i] * nl.reduce(
              i
              , pos_i
              , thrust::make_tuple(0.0, 0.0)
              , PARTICLE_LAMBDA_DEVICE(int i, int j, thrust::tuple<double, double>& value)
              {
                int type_j = *(type_first + j);
                if (categories[type_j] == static_cast<int>(category_t::ghost))
                  return;
                auto pressure_j = *(pressure_first + j);
                auto pos_j = *(pred_position_first + j);
                auto d = pos_j - pos_i;
                double rsq = particle::geometry::length_square(d);
                double r = sqrt(rsq);
                value = particle::geometry::as<thrust::tuple<double, double>>(
                  value + d * (pressure_j + pressure_i) / rsq * kernel(r));
              }));
      });

    thrust::transform(
      col.begin<tag::pred_velocity>()
      , col.end<tag::pred_velocity>()
      , col.begin<tag::pressure_grad>()
      , col.begin<tag::velocity>()
      , PARTICLE_LAMBDA(
        const thrust::tuple<double, double>& vel
        , const thrust::tuple<double, double>& grad)
      {
        return particle::geometry::as<thrust::tuple<double, double>>(vel - grad * dt);
      });

    thrust::transform(
      col.begin<tag::pred_position>()
      , col.end<tag::pred_position>()
      , col.begin<tag::pressure_grad>()
      , col.begin<tag::position>()
      , PARTICLE_LAMBDA(
        const thrust::tuple<double, double>& pos
        , const thrust::tuple<double, double>& grad)
      {
        return particle::geometry::as<thrust::tuple<double, double>>(pos - grad * dt * dt);
      });

    if ((step + 1) % ip.steps_per_output == 0)
    {
      thrust::copy(col.begin<output_tags>(), col.end<output_tags>(), h_col.begin<output_tags>());
      std::stringstream ss;
      ss << ip.output_filename << "_" << step + 1 << ".vtu";
      particle::io::vtk::save(
        ss.str()
        , h_col.begin<tag::position>()
        , h_col.end<tag::position>()
        , boost::fusion::make_vector("id", "type", "pnd", "pressure", "velocity")
        , boost::fusion::make_vector(
          h_col.begin<tag::id>()
          , h_col.begin<tag::type>()
          , h_col.begin<tag::pnd>()
          , h_col.begin<tag::pressure>()
          , h_col.begin<tag::velocity>()));
    }
  }

  return 0;
}
