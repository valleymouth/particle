#pragma once

// Thrust headers
#include <thrust/iterator/zip_iterator.h>

// Boost headers
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#pragma push
#pragma diag_suppress = probable_guiding_friend
#include <boost/fusion/container/map.hpp>
#pragma pop
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>

namespace particle
{
  template <typename... T>
  class collection
  {
    boost::fusion::map<T...> m_attrs;
    std::size_t m_size;
  
    template <typename, typename, typename, typename>
    struct begin_impl_seq;

    template <typename Seq, typename First, typename Last>
    struct begin_impl_seq<Seq, First, Last, std::true_type>
    {
      template <typename Map, typename... Attrs>
      static constexpr auto call(Map&, Attrs... attrs)
      {
        return thrust::make_zip_iterator(thrust::make_tuple(attrs...));
      }
    };

    template <typename Seq, typename First, typename Last>
    struct begin_impl_seq<Seq, First, Last, std::false_type>
    {
      template <typename Map, typename... Attrs>
      static constexpr auto call(Map& map, Attrs... attrs)
      {
        using next_type = typename boost::mpl::next<First>::type;
        return begin_impl_seq<
          Seq
          , next_type
          , Last
          , typename std::is_same<next_type, Last>::type
          >::call(map
                  , attrs...
                  , boost::fusion::at_key<
                  typename boost::mpl::deref<First>::type
                  >(map).begin());
      }
    };
  
    template <typename, typename>
    struct begin_impl;

    template <typename Attr>
    struct begin_impl<Attr, boost::mpl::true_>
    {
      template <typename Map>
      static constexpr auto call(Map& map)
      {
        using first_type = typename boost::mpl::begin<Attr>::type;
        using last_type = typename boost::mpl::end<Attr>::type;
        return begin_impl_seq<Attr, first_type, last_type, typename std::is_same<first_type, last_type>::type>::call(map);
      }
    };

    template <typename Attr>
    struct begin_impl<Attr, boost::mpl::false_>
    {
      template <typename Map>
      static constexpr auto call(Map& map)
      {
        return boost::fusion::at_key<Attr>(map).begin();
      }
    };

    template <typename, typename, typename, typename>
    struct end_impl_seq;

    template <typename Seq, typename First, typename Last>
    struct end_impl_seq<Seq, First, Last, std::true_type>
    {
      template <typename Map, typename... Attrs>
      static constexpr auto call(Map&, Attrs... attrs)
      {
        return thrust::make_zip_iterator(thrust::make_tuple(attrs...));
      }
    };

    template <typename Seq, typename First, typename Last>
    struct end_impl_seq<Seq, First, Last, std::false_type>
    {
      template <typename Map, typename... Attrs>
      static constexpr auto call(Map& map, Attrs... attrs)
      {
        using next_type = typename boost::mpl::next<First>::type;
        return end_impl_seq<
          Seq
          , next_type
          , Last
          , typename std::is_same<next_type, Last>::type
          >::call(map
                  , attrs...
                  , boost::fusion::at_key<
                  typename boost::mpl::deref<First>::type
                  >(map).end());
      }
    };
  
    template <typename, typename>
    struct end_impl;

    template <typename Attr>
    struct end_impl<Attr, boost::mpl::true_>
    {
      template <typename Map>
      static constexpr auto call(Map& map)
      {
        using first_type = typename boost::mpl::begin<Attr>::type;
        using last_type = typename boost::mpl::end<Attr>::type;
        return end_impl_seq<Attr, first_type, last_type, typename std::is_same<first_type, last_type>::type>::call(map);
      }
    };

    template <typename Attr>
    struct end_impl<Attr, boost::mpl::false_>
    {
      template <typename Map>
      static constexpr auto call(Map& map)
      {
        return boost::fusion::at_key<Attr>(map).end();
      }
    };

  public:
    using all = typename boost::mpl::transform<
    boost::mpl::vector<T...>
    , boost::fusion::result_of::first<boost::mpl::_>
    >::type;
  
    collection(): m_size(0) {};

    auto begin()
    {
      return begin_impl<all, boost::mpl::true_>::call(m_attrs);
    }
  
    auto begin() const
    {
      return const_cast<collection*>(this)->begin();
    }
  
    template <typename Attr>
    auto begin()
    {
      return begin_impl<Attr, typename boost::mpl::is_sequence<Attr>::type>::call(m_attrs);
    }

    template <typename Attr>
    auto begin() const
    {
      return const_cast<collection*>(this)->begin<Attr>();
    }

    auto end()
    {
      return end_impl<all, boost::mpl::true_>::call(m_attrs);
    }

    auto end() const
    {
      return const_cast<collection*>(this)->end();
    }
  
    template <typename Attr>
    auto end()
    {
      return end_impl<Attr, typename boost::mpl::is_sequence<Attr>::type>::call(m_attrs);
    }

    template <typename Attr>
    auto end() const
    {
      return const_cast<collection*>(this)->end<Attr>();
    }
  
    void resize(std::size_t size)
    {
      boost::fusion::for_each(m_attrs, [=](auto &x) { x.second.resize(size); });
      m_size = size;
    }

    std::size_t size() const
    {
      return m_size;
    }
  };
} // namespace particle
