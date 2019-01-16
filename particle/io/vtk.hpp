#pragma once

// Particle headers
#include <particle/geometry/dim.hpp>
#include <particle/geometry/elem.hpp>
#include <particle/geometry/value_type.hpp>

// VTK headers
#include <vtkCharArray.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>
#include <vtkShortArray.h>
#include <vtkSmartPointer.h>
#include <vtkUnsignedShortArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>

// Boost headers
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/transform.hpp>

// Std headers
#include <iterator>

namespace particle
{
namespace io
{
namespace vtk
{
  namespace detail
  {
    template <typename T>
    struct std_pair_second_type
    {
      using type = typename T::second_type;
    };
    
    template <typename T>
    struct iterator_value_type
    {
      using type = typename std::iterator_traits<T>::value_type;
    };

    template <typename T>
    struct make_array_ptr
    {
      using type = typename boost::mpl::if_<
        std::is_same<char, T>
        , vtkSmartPointer<vtkCharArray>
        , typename boost::mpl::if_<
            std::is_same<short, T>
            , vtkSmartPointer<vtkShortArray>
            , typename boost::mpl::if_<
                std::is_same<int, T>
                , vtkSmartPointer<vtkIntArray>
                , typename boost::mpl::if_<
                    std::is_same<float, T>
                    , vtkSmartPointer<vtkFloatArray>
                    , vtkSmartPointer<vtkDoubleArray>
                    >::type
                >::type
            >::type
        >::type;
    };

    template <class Array, class T>
    inline void insert_next_point(Array array, const thrust::tuple<T, T>& t)
    {
      using particle::geometry::elem;

      array->InsertNextPoint(elem<0>(t), elem<1>(t), 0);
    }

    template <class Array, class T>
    inline void insert_next_point(Array array, const thrust::tuple<T, T, T>& t)
    {
      using particle::geometry::elem;

      array->InsertNextPoint(elem<0>(t), elem<1>(t), elem<2>(t));
    }

    // Need enable_if to prevent the compiler from choosing this function for
    // tuples.
    template <
      class Array
      , class T
      , typename std::enable_if<
          particle::geometry::traits::dim<T>::value == 1, int>::type = 0>
    inline void insert_next_value(Array array, T x)
    {
      array->InsertNextValue(x);
    }

    template <class Array, class T>
    inline void insert_next_value(Array array, const thrust::tuple<T, T>& t)
    {
      using particle::geometry::elem;

      array->InsertNextTuple2(elem<0>(t), elem<1>(t));
    }

    template <class Array, class T>
    inline void insert_next_value(Array array, const thrust::tuple<T, T, T>& t)
    {
      using particle::geometry::elem;

      array->InsertNextTuple3(elem<0>(t), elem<1>(t), elem<2>(t));
    }
  } // namespace detail
  
  template <typename InputIterator, typename Names, typename Attrs>
  void save(
    const std::string& filename
    , InputIterator position_first
    , InputIterator position_last
    , Names names
    , Attrs attrs)
  {
    using arrays_type = typename boost::mpl::transform<
      Attrs
      , detail::make_array_ptr<
        particle::geometry::traits::value_type<
          detail::iterator_value_type<boost::mpl::_>>>>::type;
    arrays_type arrays;
    using zip_vector_type = boost::fusion::vector<Names&, Attrs&, arrays_type&>;
    using zip_type = boost::fusion::zip_view<zip_vector_type>;
    zip_type zip(zip_vector_type(names, attrs, arrays));
    boost::fusion::for_each(
      zip
      , [](auto x)
      {
        using boost::fusion::at_c;
        at_c<2>(x) = std::remove_reference<decltype(at_c<2>(x))>::type::New();
        at_c<2>(x)->SetName(at_c<0>(x));
        at_c<2>(x)->SetNumberOfComponents(
          particle::geometry::traits::dim<
          typename detail::iterator_value_type<
          typename std::remove_reference<decltype(at_c<1>(x))>::type
          >::type>::value);
      });

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->Allocate(std::distance(position_first, position_last));

    for (InputIterator it = position_first; it != position_last; ++it)
    {
      detail::insert_next_point(points, *it);
      boost::fusion::for_each(
        zip
        , [](auto x)
        {
          using boost::fusion::at_c;
          detail::insert_next_value(at_c<2>(x), *at_c<1>(x));
          ++at_c<1>(x);
        });
    }

    vtkSmartPointer<vtkUnstructuredGrid> grid =
      vtkSmartPointer<vtkUnstructuredGrid>::New();
    grid->SetPoints(points);
    boost::fusion::for_each(
      zip
      , [&](auto x)
      {
        using boost::fusion::at_c;
        grid->GetPointData()->SetActiveScalars("");
        grid->GetPointData()->SetScalars(at_c<2>(x));
      });

    vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
      vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer->SetFileName(filename.c_str());
    writer->SetInputData(grid);
    writer->SetDataModeToBinary();
    writer->Write();
  }
} // namespace vtk
} // namespace io
} // namespace particle
