/*---------------------------------------------------------------------------*/
/*! @created   : 2005/04/28                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 6.0.0                                                       */
/*! @filename  : args.hpp                                                    */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's argument type       */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_ARGS_HPP__INCLUDED
#define E3475__HYDRA_ARGS_HPP__INCLUDED 600

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's argument type template                 //
//---------------------------------------------------------------------------//
template <
    typename CodeType  = char
  , typename Primitive = int
  , typename ValueType = unsigned int
  , typename Container = std::vector<ValueType>
  , typename Exception = std::exception>
struct hydra_args
{
    typedef CodeType        code_type;      // Input/Output value type
    typedef Primitive       primitive;      // Hydra's primitive type
    typedef Container       container;      // Hydra's container core type
    typedef Exception       exception;      // Hydra's exception core type

    typedef typename container::size_type               size_type;
    typedef typename container::size_type               digit_type;
    typedef typename container::value_type              value_type;
    typedef typename container::allocator_type          allocator_type;
    typedef typename container::reference               reference;
    typedef typename container::const_reference         const_reference;
    typedef typename container::difference_type         difference_type;
    typedef typename container::iterator                iterator;
    typedef typename container::const_iterator          const_iterator;
    typedef typename container::reverse_iterator        reverse_iterator;
    typedef typename container::const_reverse_iterator  const_reverse_iterator;
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_ARGS_HPP__INCLUDED
