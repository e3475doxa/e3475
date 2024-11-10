/*---------------------------------------------------------------------------*/
/*! @created   : 2005/07/31                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 2.0.0                                                       */
/*! @filename  : viscera.hpp                                                 */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's viscera type        */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_VISCERA_HPP__INCLUDED
#define E3475__HYDRA_VISCERA_HPP__INCLUDED 200

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's viscera type template                  //
//---------------------------------------------------------------------------//
template <typename HydraArgs>
struct hydra_viscera
{
    typedef HydraArgs                       args;
    typedef hydra_viscera<args>             selves;
    typedef typename args::container        container;
    typedef typename args::value_type       value_type;
    typedef typename args::digit_type       digit_type;
    typedef typename args::allocator_type   allocator_type;

    bool           sign_flag_;         // maintenance sign flag
    container      container_;         // maintenance container
    value_type     radix_value_;       // maintenance radix value

    /*------------------------------------------------------------*/
    /*! @brief   : copy constructor                               */
    /*------------------------------------------------------------*/
    hydra_viscera(
        const selves&   src) 
    : sign_flag_(src.sign_flag_)
    , container_(src.container_)
    , radix_value_(src.radix_value_)
    {
    }

    /*------------------------------------------------------------*/
    /*! @brief   : constructor for sign and container             */
    /*------------------------------------------------------------*/
    hydra_viscera(
        const bool&         sign
      , const container&    src
      , const value_type&   radix)
    : sign_flag_(sign)
    , container_(src)
    , radix_value_(radix)
    {
    }

    /*------------------------------------------------------------*/
    /*! @brief   : constructor for sign and container allloc type */
    /*------------------------------------------------------------*/
    hydra_viscera(
        const bool&             sign
      , const value_type&       radix
      , const allocator_type&   allloc)
    : sign_flag_(sign)
    , container_(allloc)
    , radix_value_(radix)
    {
    }

    /*------------------------------------------------------------*/
    /*! @brief   : constructor for designate digits and values    */
    /*------------------------------------------------------------*/
    hydra_viscera(
        const bool&             sign
      , const digit_type&       digit
      , const value_type&       value
      , const value_type&       radix
      , const allocator_type&   alloc)
    : sign_flag_(sign)
    , container_(digit, value, alloc)
    , radix_value_(radix)
    {
    }

    /*------------------------------------------------------------*/
    /*! @brief   : constructor for container's const iterator     */
    /*------------------------------------------------------------*/
    template <typename InputIterator>
    hydra_viscera(
        const bool&             sign
      , InputIterator           first
      , InputIterator           last
      , const value_type&       radix
      , const allocator_type&   alloc)
    : sign_flag_(sign)
    , container_(first, last, alloc)
    , radix_value_(radix)
    {
    }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_VISCERA_HPP__INCLUDED
