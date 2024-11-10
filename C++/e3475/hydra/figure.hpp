/*---------------------------------------------------------------------------*/
/*! @created   : 2004/10/01                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 7.0.0                                                       */
/*! @filename  : figure.hpp                                                  */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2004-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's figure type         */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_FIGURE_HPP__INCLUDED
#define E3475__HYDRA_FIGURE_HPP__INCLUDED 700

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// class : definition for hydra's figure type template                       //
//---------------------------------------------------------------------------//
template <typename HydraGlobals>
class hydra_figure : public HydraGlobals::marrow
{
    public:
        typedef HydraGlobals                            global;
        typedef hydra_figure<global>                    selves;
        typedef typename global::args                   args;
        typedef typename global::range                  range;
        typedef typename global::marrow                 marrow;
        typedef typename global::viscera                viscera;
        typedef typename global::exception              exception;
        typedef typename args::container                container;
        typedef typename args::size_type                size_type;
        typedef typename args::value_type               value_type;
        typedef typename args::digit_type               digit_type;
        typedef typename args::allocator_type           allocator_type;
        typedef typename args::reference                reference;
        typedef typename args::const_reference          const_reference;
        typedef typename args::difference_type          difference_type;
        typedef typename args::iterator                 iterator;
        typedef typename args::const_iterator           const_iterator;
        typedef typename args::reverse_iterator         reverse_iterator;
        typedef typename args::const_reverse_iterator   const_reverse_iterator;

    private:
        viscera     viscera_;       // maintenance hydra viscera

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : destructor                                     */
        /*------------------------------------------------------------*/
        virtual ~hydra_figure() throw()
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : default constructor                            */
        /*------------------------------------------------------------*/
        explicit hydra_figure(
            const allocator_type&   allloc = allocator_type())
        : viscera_(global::get_sign_flag(), global::get_keeping_radix(), allloc)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : copy constructor                               */
        /*------------------------------------------------------------*/
        hydra_figure(
            const selves&   src)
        : viscera_(src.viscera_)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for marrow container               */
        /*------------------------------------------------------------*/
        hydra_figure(
            const marrow&  src) 
        : viscera_(src.get_sign_flag(), src, src.get_radix_value())
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for marrow container with parameter*/
        /*------------------------------------------------------------*/
        hydra_figure(
            const marrow&  src
          , const bool&    sign)
        : viscera_(sign, src, src.get_radix_value())
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for container                      */
        /*------------------------------------------------------------*/
        explicit hydra_figure(
            const container&    src
          , const bool&         sign  = global::get_sign_flag()
          , const value_type&   radix = global::get_keeping_radix())
        : viscera_(sign, src, radix)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for designate digits and values    */
        /*------------------------------------------------------------*/
        explicit hydra_figure(
            const digit_type&       digit
          , const value_type&       value = value_type()
          , const bool&             sign  = global::get_sign_flag()
          , const value_type&       radix = global::get_keeping_radix()
          , const allocator_type&   alloc = allocator_type())
        : viscera_(sign, digit, value, radix, alloc)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for etcetera type                  */
        /*------------------------------------------------------------*/
        template <typename EtcType>
        explicit hydra_figure(
            const bool&             sign
          , const EtcType&          value
          , const value_type&       radix = global::get_keeping_radix()
          , const allocator_type&   alloc = allocator_type())
        : viscera_(sign, 1, value, radix, alloc)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for etc container's iterator       */
        /*------------------------------------------------------------*/
        template <typename InputIterator>
        explicit hydra_figure(
            InputIterator           first
          , InputIterator           last
          , const bool&             sign  = global::get_sign_flag()
          , const value_type&       radix = global::get_keeping_radix()
          , const allocator_type&   alloc = allocator_type())
        : viscera_(sign, first, last, radix, alloc)
        {
        }

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : set new sign flag                              */
        /*------------------------------------------------------------*/
        void set_sign_flag(
            const bool&     flag) throw()
        {
            selves::viscera_.sign_flag_ = flag;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : get present sign flag                          */
        /*------------------------------------------------------------*/
        const bool& get_sign_flag() const throw()
        {
            return selves::viscera_.sign_flag_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : set new radix value                            */
        /*------------------------------------------------------------*/
        virtual void set_radix_value(
            const value_type&   radix)
        {
            selves::viscera_.radix_value_ = radix;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : get present radix value                        */
        /*------------------------------------------------------------*/
        const value_type& get_radix_value() const throw()
        {
            return selves::viscera_.radix_value_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns selves allocator                       */
        /*------------------------------------------------------------*/
        allocator_type get_allocator() const
        {
            return selves::viscera_.container_.get_allocator();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : erases values and copies specified elements    */
        /*------------------------------------------------------------*/
        void assign(
            const digit_type&   digit
          , const value_type&   value = value_type()
          , const bool&         sign  = global::get_sign_flag()
          , const value_type&   radix = global::get_keeping_radix())
        {
            selves::set_sign_flag(sign);
            selves::set_radix_value(radix);
            selves::viscera_.container_.assign(digit, value);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : erases values and copies specified iterator    */
        /*------------------------------------------------------------*/
        void assign(
            const_iterator      first
          , const_iterator      last
          , const bool&         sign  = global::get_sign_flag()
          , const value_type&   radix = global::get_keeping_radix())
        {
            selves::set_sign_flag(sign);
            selves::set_radix_value(radix);
            selves::viscera_.container_.assign(first, last);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : erases values and copies etceteras iterator    */
        /*------------------------------------------------------------*/
        template <typename InputIterator>
        void assign(
            InputIterator       first
          , InputIterator       last
          , const bool&         sign  = global::get_sign_flag()
          , const value_type&   radix = global::get_keeping_radix())
        {
            selves::set_sign_flag(sign);
            selves::set_radix_value(radix);
            selves::viscera_.container_.assign(first, last);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns reference from specified element       */
        /*------------------------------------------------------------*/
        reference at(
            const digit_type&   position)
        {
            return (*this)[position];
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns const reference from specified element */
        /*------------------------------------------------------------*/
        const_reference at(
            const digit_type&   position) const
        {
            return (*this)[position];
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns first iterator from elements           */
        /*------------------------------------------------------------*/
        iterator begin()
        {
            return selves::viscera_.container_.begin();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns first const iterator from elements     */
        /*------------------------------------------------------------*/
        const_iterator begin() const
        {
            return selves::viscera_.container_.begin();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns capacity size of container             */
        /*------------------------------------------------------------*/
        digit_type capacity() const
        {
            return selves::viscera_.container_.capacity();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : erases elements of values                      */
        /*------------------------------------------------------------*/
        void clear()
        {
            selves::viscera_.container_.clear();
            selves::set_sign_flag(global::get_sign_flag());
        }

        /*------------------------------------------------------------*/
        /*! @brief   : checks empty                                   */
        /*------------------------------------------------------------*/
        bool empty() const
        {
            return selves::viscera_.container_.empty();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns last iterator from elements            */
        /*------------------------------------------------------------*/
        iterator end()
        {
            return selves::viscera_.container_.end();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns last const iterator from elements      */
        /*------------------------------------------------------------*/
        const_iterator end() const
        {
            return selves::viscera_.container_.end();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : removes specified element                      */
        /*------------------------------------------------------------*/
        iterator erase(
            iterator&   where)
        {
            return selves::viscera_.container_.erase(where);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : removes range of specified elements            */
        /*------------------------------------------------------------*/
        iterator erase(
            iterator&   first,
            iterator&   last)
        {
            return selves::viscera_.container_.erase(first, last);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns maximum size                           */
        /*------------------------------------------------------------*/
        digit_type max_size() const
        {
            return selves::viscera_.container_.max_size();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : adds value to end of elements                  */
        /*------------------------------------------------------------*/
        void push_back(
            const value_type&   value)
        {
            selves::viscera_.container_.push_back(value);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed first iterator                */
        /*------------------------------------------------------------*/
        reverse_iterator rbegin()
        {
            return selves::viscera_.container_.rbegin();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed first const iterator          */
        /*------------------------------------------------------------*/
        const_reverse_iterator rbegin() const
        {
            return selves::viscera_.container_.rbegin();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed last iterator                 */
        /*------------------------------------------------------------*/
        reverse_iterator rend()
        {
            return selves::viscera_.container_.rend();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed last const iterator           */
        /*------------------------------------------------------------*/
        const_reverse_iterator rend() const
        {
            return selves::viscera_.container_.rend();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : reserves minimum length of storage             */
        /*------------------------------------------------------------*/
        void reserve(
            const digit_type&   reserve_size)
        {
            selves::viscera_.container_.reserve(reserve_size);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : specifies new size                             */
        /*------------------------------------------------------------*/
        void resize(
            const digit_type&   size
          , const value_type&   value = value_type())
        {
            selves::viscera_.container_.resize(size, value);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns size of elements                       */
        /*------------------------------------------------------------*/
        digit_type size() const
        {
            return selves::viscera_.container_.size();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitutions                                  */
        /*------------------------------------------------------------*/
        selves& operator= (
            const selves&   src)
        {
            selves::assign( src.begin()
                          , src.end()
                          , src.get_sign_flag()
                          , src.get_radix_value());
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns reference from specified element       */
        /*------------------------------------------------------------*/
        reference operator[](
            const digit_type&   position)
        {
            return selves::viscera_.container_[position];
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns const reference from specifiedelement  */
        /*------------------------------------------------------------*/
        const_reference operator[](
            const digit_type&   position) const
        {
            return selves::viscera_.container_[position];
        }

        /*------------------------------------------------------------*/
        /*! @brief   : refers figure container type                   */
        /*------------------------------------------------------------*/
        operator container&()
        {
            return selves::viscera_.container_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : refers const figure container type             */
        /*------------------------------------------------------------*/
        operator const container&() const
        {
            return selves::viscera_.container_;
        }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_FIGURE_HPP__INCLUDED
