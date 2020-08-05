//
//  Copyright (c) 2018-2020, Cem Bassoy, cem.bassoy@gmail.com
//  Copyright (c) 2019-2020, Amit Singh, amitsingh19975@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Google
//
/// \file strides.hpp Definition for the basic_strides template class

#ifndef BOOST_UBLAS_TENSOR_STATIC_STRIDES_HPP
#define BOOST_UBLAS_TENSOR_STATIC_STRIDES_HPP

#include <boost/numeric/ublas/tensor/static_extents.hpp>
#include <boost/numeric/ublas/tensor/layout.hpp>
#include <boost/numeric/ublas/tensor/detail/static_extents_traits.hpp>

namespace boost::numeric::ublas{

  template <class E, class L> class basic_static_strides;

} // boost::numeric::ublas

namespace boost::numeric::ublas::detail{

  // list for storing stides as types
  template< typename T, T... P > 
  struct static_stride_list{
      using extents_type = basic_static_extents<T, P...>;
      using type = std::array<T, sizeof...(P)>;
      static constexpr type const value = {P...};
  };

  namespace impl{
 
    // concat two static_stride_list togather
    // @code using type = typename concat< static_stride_list<int, 1,2,3>, static_stride_list<int, 4,5,6> >::type @endcode
    template<typename L1, typename L2>
    struct concat;

    template<typename T, T... N1, T... N2>
    struct concat< static_stride_list<T, N1...>, static_stride_list<T, N2...> > {
      using type = static_stride_list<T, N1..., N2...>;
    };

    template<typename L1, typename L2>
    using concat_t = typename concat<L1,L2>::type;

    // generates static_stride_list containing ones with specific size
    template<typename T, std::size_t N> 
    struct make_sequence_of_ones;

    template<typename T, std::size_t N> 
    using make_sequence_of_ones_t = typename make_sequence_of_ones<T, N>::type;

    template<typename T, std::size_t N>
    struct make_sequence_of_ones {
      using type = concat_t<make_sequence_of_ones_t<T, N/2>, make_sequence_of_ones_t<T, N - N/2>>;
    };

    template<typename T> 
    struct make_sequence_of_ones<T, 0ul> {
      using type = static_stride_list<T>;
    };
    template<typename T> 
    struct make_sequence_of_ones<T, 1ul>{ 
      using type = static_stride_list<T, T(1)>;
    };

  } // impl


  template<typename T, std::size_t N> 
  using make_sequence_of_ones_t = impl::make_sequence_of_ones_t<T,N>;

  // @returns the static_stride_list containing strides
  // It is a helper function or implementation
  template<typename L, typename T, T E0, T... E, T... R, T... P>
  constexpr auto make_static_strides_helper( 
    [[maybe_unused]] static_stride_list<T, E0, E...> e1, 
    [[maybe_unused]] static_stride_list<T, R...> e2, 
    [[maybe_unused]] static_stride_list<T, P...> e3
  ){
      if constexpr(sizeof...(E) == 0ul ){
        
        if constexpr( std::is_same_v<layout::last_order, L> ){

          return static_stride_list<T, P..., E0>{};
          
        }else{

          return static_stride_list<T, P...>{};

        }

      }else{
        // add extent to the list, which will be used for
        // taking the product for next iteration
        auto n = static_stride_list<T, R...,E0>{};

        // result list containing the strides
        // on each iteration calculate the product
        if constexpr( std::is_same_v<layout::last_order, L> ){
          auto np = static_stride_list< T, P..., product( basic_static_extents<T, E..., E0>{} ) >{};
          return make_static_strides_helper<L>( static_stride_list<T, E...>{}, n, np );
        }else{
          auto np = static_stride_list< T, P..., product( basic_static_extents<T, R..., E0>{} ) >{};
          return make_static_strides_helper<L>( static_stride_list<T, E...>{}, n, np );
        }
      }

  }


  // @returns the static_stride_list containing strides for last order
  template<typename L, typename T, T E0, T... E>
  constexpr auto make_static_strides( [[maybe_unused]] static_stride_list<T, E0, E...> e )
  {
    using extents_type = typename static_stride_list<T, E0, E...>::extents_type;
    // checks if extents are vector or scalar
    if constexpr( !( static_traits::is_scalar_v<extents_type> || static_traits::is_vector_v<extents_type> ) ){
      // if extent contains only one element return static_stride_list<T,T(1)>
      if constexpr( sizeof...(E) == 0 ){
        
        return static_stride_list<T,T(1)>{};

      }else{
        
        if constexpr( std::is_same_v<L, layout::first_order > ){
          
          using ret_type = decltype( make_static_strides_helper<L>(static_stride_list<T, E0, E...>{}, static_stride_list<T>{}, static_stride_list<T>{}) );
          return impl::concat_t< static_stride_list<T, T(1)>, ret_type>{};

        }else{

          using ret_type = decltype( make_static_strides_helper<L>(static_stride_list<T, E...>{}, static_stride_list<T>{}, static_stride_list<T>{}) );
          return impl::concat_t<ret_type, static_stride_list<T, T(1)> >{};

        }

      }
    }else{
      // @returns list contining ones if it is vector or scalar
      return make_sequence_of_ones_t<T, sizeof...(E) + 1>{};
    }
  }
  
  // if extents are empty return empty list
  template<typename L, typename T>
  constexpr auto make_static_strides( [[maybe_unused]] static_stride_list<T> e )
  {
    return static_stride_list<T>{};
  }

  // It is use for first order to
  // get std::array containing strides
  template<typename Layout, typename T, T... E>
  struct strides_helper{
    using type = decltype( make_static_strides<Layout>(static_stride_list<T, E...>{}) );
    static constexpr auto value = type::value;
  };

  template<typename Layout, typename T, T... E>
  inline static constexpr auto strides_helper_v = strides_helper<Layout, T, E...>::value;

} // namespace boost::numeric::ublas::detail

namespace boost::numeric::ublas
{
/** @brief Partial Specialization for layout::first_order or column_major
 *
 * @code basic_static_strides<basic_static_extents<4,1,2,3,4>, layout::first_order> s @endcode
 *
 * @tparam R rank of basic_static_extents
 * @tparam Extents paramerter pack of extents
 *
 */
template <class Layout, class T, T... Extents>
class basic_static_strides<basic_static_extents<T,Extents...>, Layout>
{

public:

  static constexpr std::size_t const _size = sizeof...(Extents);

  using layout_type     = Layout;
  using extents_type    = basic_static_extents<T,Extents...>;
  using base_type       = std::array<T, _size>;
  using value_type      = typename base_type::value_type;
  using reference       = typename base_type::reference;
  using const_reference = typename base_type::const_reference;
  using size_type       = typename base_type::size_type;
  using const_pointer   = typename base_type::const_pointer;
  using const_iterator  = typename base_type::const_iterator;
  using const_reverse_iterator = typename base_type::const_reverse_iterator;

  /**
   * @param k pos of extent
   * @returns the element at given pos
   */
  [[nodiscard]] inline 
  constexpr const_reference at(size_type k) const 
  {
    return m_data.at(k);
  }

  [[nodiscard]] inline 
  constexpr const_reference operator[](size_type k) const { return m_data[k]; }

  //@returns the rank of basic_static_extents
  [[nodiscard]] inline 
  constexpr size_type size() const noexcept { return static_cast<size_type>(_size); }

  [[nodiscard]] inline
  constexpr const_reference back () const{
      return m_data.back();
  }

  // default constructor
  constexpr basic_static_strides() noexcept{
    static_assert( 
      _size == 0 || 
      ( static_traits::is_valid_v<extents_type> &&
        ( static_traits::is_vector_v<extents_type> ||
          static_traits::is_scalar_v<extents_type> ||
          _size >= 2 
        )
      )
      , 
      "Error in boost::numeric::ublas::basic_static_strides() : "
      "Size can be 0 or Shape should be valid and shape can be vector or shape can be scalar or size should be greater than"
      " or equal to 2"
    ); 	
    
    
  }

  constexpr basic_static_strides(extents_type const& e) noexcept{ (void)e; };

  // default copy constructor
  constexpr basic_static_strides(basic_static_strides const &other) noexcept = default;
  constexpr basic_static_strides(basic_static_strides &&other) noexcept = default;
  
  // default assign constructor
  constexpr basic_static_strides &
  operator=(basic_static_strides const &other) noexcept = default;
  
  constexpr basic_static_strides &
  operator=(basic_static_strides &&other) noexcept = default;

  ~basic_static_strides() = default;

   /** @brief Returns ref to the std::array containing extents */
  [[nodiscard]] inline
  constexpr auto const& base() const noexcept{
    return m_data;
  }

  /** @brief Returns pointer to the std::array containing extents */
  [[nodiscard]] inline
  constexpr const_pointer data() const noexcept{
    return m_data.data();
  }

  [[nodiscard]] inline
  constexpr const_iterator begin() const noexcept{
    return m_data.begin();
  }

  [[nodiscard]] inline
  constexpr const_iterator end() const noexcept{
    return m_data.end();
  }

  [[nodiscard]] inline
  constexpr bool empty() const noexcept{
    return m_data.empty();
  }

  [[nodiscard]] inline
  constexpr const_reverse_iterator
  rbegin() const noexcept
  {
      return m_data.rbegin();
  }

  [[nodiscard]] inline
  constexpr const_reverse_iterator
  rend() const noexcept
  {
      return m_data.rend();
  }

private:
  static constexpr base_type const m_data{ detail::strides_helper_v<layout_type,T,Extents...> };
};

} // namespace boost::numeric::ublas

#endif
