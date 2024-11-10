/*---------------------------------------------------------------------------*/
/*! @created   : 2005/05/10                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 3.0.0                                                       */
/*! @filename  : marrow.hpp                                                  */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's marrow type         */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_MARROW_HPP__INCLUDED
#define E3475__HYDRA_MARROW_HPP__INCLUDED 300

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// class : definition for hydra's marrow type template                       //
//---------------------------------------------------------------------------//
template <typename HydraArgs>
class hydra_marrow
{
    public:
        typedef HydraArgs                               args;
        typedef hydra_marrow<args>                      selves;
        typedef typename args::container                container;
        typedef typename args::value_type               value_type;
        typedef typename args::digit_type               digit_type;
        typedef typename args::allocator_type           allocator_type;
        typedef typename args::reference                reference;
        typedef typename args::const_reference          const_reference;
        typedef typename args::iterator                 iterator;
        typedef typename args::const_iterator           const_iterator;
        typedef typename args::reverse_iterator         reverse_iterator;
        typedef typename args::const_reverse_iterator   const_reverse_iterator;

    protected:
        /*------------------------------------------------------------*/
        /*! @brief   : destructor                                     */
        /*------------------------------------------------------------*/
        virtual ~hydra_marrow() throw() {}

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : set new sign flag                              */
        /*------------------------------------------------------------*/
        virtual void set_sign_flag(
            const bool&     flag) throw() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : get present sign flag                          */
        /*------------------------------------------------------------*/
        virtual const bool& get_sign_flag() const throw() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : set new radix value                            */
        /*------------------------------------------------------------*/
        virtual void set_radix_value(
            const value_type&   radix) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : get present radix value                        */
        /*------------------------------------------------------------*/
        virtual const value_type& get_radix_value() const throw() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns selves allocator                       */
        /*------------------------------------------------------------*/
        virtual allocator_type get_allocator() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : erases values and copies specified elements    */
        /*------------------------------------------------------------*/
        virtual void assign(
            const digit_type&   digit
          , const value_type&   value
          , const bool&         sign
          , const value_type&   radix) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : erases values and copies specified iterator    */
        /*------------------------------------------------------------*/
        virtual void assign(
            const_iterator      first
          , const_iterator      last
          , const bool&         sign
          , const value_type&   radix) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns reference from core elements           */
        /*------------------------------------------------------------*/
        virtual reference at(
            const digit_type&   position) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns const reference from core elements     */
        /*------------------------------------------------------------*/
        virtual const_reference at(
            const digit_type&   position) const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns first iterator from core elements      */
        /*------------------------------------------------------------*/
        virtual iterator begin() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns first const iterator from core elements*/
        /*------------------------------------------------------------*/
        virtual const_iterator begin() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns capacity size of container             */
        /*------------------------------------------------------------*/
        virtual digit_type capacity() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : erases elements of values                      */
        /*------------------------------------------------------------*/
        virtual void clear() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : checks empty                                   */
        /*------------------------------------------------------------*/
        virtual bool empty() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns last iterator from core elements       */
        /*------------------------------------------------------------*/
        virtual iterator end() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns last const iterator from core elements */
        /*------------------------------------------------------------*/
        virtual const_iterator end() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : remove element                                 */
        /*------------------------------------------------------------*/
        virtual iterator erase(
            iterator&   where) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : removes range of elements                      */
        /*------------------------------------------------------------*/
        virtual iterator erase(
            iterator&   first,
            iterator&   last) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns maximum size                           */
        /*------------------------------------------------------------*/
        virtual digit_type max_size() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : adds value to end of elements                  */
        /*------------------------------------------------------------*/
        virtual void push_back(
            const value_type&   value) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed first iterator                */
        /*------------------------------------------------------------*/
        virtual reverse_iterator rbegin() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed first const iterator          */
        /*------------------------------------------------------------*/
        virtual const_reverse_iterator rbegin() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed last iterator                 */
        /*------------------------------------------------------------*/
        virtual reverse_iterator rend() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns reversed last const iterator           */
        /*------------------------------------------------------------*/
        virtual const_reverse_iterator rend() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : reserves minimum length of storage             */
        /*------------------------------------------------------------*/
        virtual void reserve(
            const digit_type&   reserve_size) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : specifies new size                             */
        /*------------------------------------------------------------*/
        virtual void resize(
            const digit_type&   size,
            const value_type&   value) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns size of elements                       */
        /*------------------------------------------------------------*/
        virtual digit_type size() const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns reference from core elements           */
        /*------------------------------------------------------------*/
        virtual reference operator[](
            const digit_type&   position) = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : returns const reference from core elements     */
        /*------------------------------------------------------------*/
        virtual const_reference operator[](
            const digit_type&   position) const = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : refers core container type                     */
        /*------------------------------------------------------------*/
        virtual operator container&() = 0;

        /*------------------------------------------------------------*/
        /*! @brief   : refers const core container type               */
        /*------------------------------------------------------------*/
        virtual operator const container&() const = 0;
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_MARROW_HPP__INCLUDED
