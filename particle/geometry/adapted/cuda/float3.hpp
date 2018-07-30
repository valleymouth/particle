#pragma once

// Particle headers
#include "../../../config.hpp"

// Boost headers
#include <boost/mpl/identity.hpp>

namespace particle
{
  namespace geometry
  {
    namespace cuda
    {
      struct float3_tag;
    }

    namespace traits
    {
      template <class>
      struct tag_of;

      template <>
      struct tag_of<float3>: boost::mpl::identity<cuda::float3_tag>
      {};
    }

    namespace extension
    {
      template <class>
      struct elem_impl;

      template <>
      struct elem_impl<cuda::float3_tag>
      {
	template <std::size_t N, class Float3>
	struct apply;
	
	template <class Float3>
	struct apply<0, Float3>
	{
	  typedef typename boost::mpl::if_<
	    boost::is_const<Float3>, const float &, float &>::type type;

	  PARTICLE_INLINE_FUNCTION
	  static type call(Float3 &v)
	  {
	    return v.x;
	  }
	};

	template <class Float3>
	struct apply<1, Float3>
	{
	  typedef typename boost::mpl::if_<
	    boost::is_const<Float3>, const float &, float &>::type type;

	  PARTICLE_INLINE_FUNCTION
	  static type call(Float3 &v)
	  {
	    return v.y;
	  }
	};

	template <class Float3>
	struct apply<2, Float3>
	{
	  typedef typename boost::mpl::if_<
	    boost::is_const<Float3>, const float &, float &>::type type;

	  PARTICLE_INLINE_FUNCTION
	  static type call(Float3 &v)
	  {
	    return v.z;
	  }
	};
      };

      template <class>
      struct dimension_of_impl;

      template <>
      struct dimension_of_impl<cuda::float3_tag>
      {
	template <class>
	struct apply: boost::mpl::int_<3>
	{};
      };

      template <class>
      struct plus_impl;

      template <>
      struct plus_impl<cuda::float3_tag>
      {
	template <class Float3>
	struct apply
	{
	  typedef float3 type;

	  MPS_HOST_AND_DEVICE
	  static type call(const Float3 &lhs, const Float3 &rhs)
	  {
	    return make_float3(lhs.x + rhs.x, lhs.y + rhs.y);
	  }
	};
      };

      template <class>
      struct value_type_impl;

      template <>
      struct value_type_impl<cuda::float3_tag>
      {
	template <class>
	struct apply: boost::mpl::identity<float>
	{};
      };

      template <class>
      struct zero_impl;

      template <>
      struct zero_impl<cuda::float3_tag>
      {
	template <class>
	struct apply
	{
	  typedef float3 type;

	  MPS_HOST_AND_DEVICE
	  static type call()
	  {
	    return make_float3(0, 0);
	  }
	};
      };
    } // namespace extension
  } // namespace geometry
} // namespace particle
