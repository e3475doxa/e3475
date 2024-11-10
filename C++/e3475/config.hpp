/*---------------------------------------------------------------------------*/
/*! @created   : 2006/01/25                                                  */
/*! @update    : 2006/01/25                                                  */
/*! @version   : 1.0.0                                                       */
/*! @filename  : config.hpp                                                  */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2006.              */
/*---------------------------------------------------------------------------*/
/*! @details   : definitions for e3475 library configurations                */
/*---------------------------------------------------------------------------*/
#ifndef E3475__CONFIG_HPP__INCLUDED
#define E3475__CONFIG_HPP__INCLUDED 100

//----------------------------------------------//
// Avoid problems on windows.h macro definition //
//----------------------------------------------//
#if (defined(__WIN32__) || defined(WIN32))
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif // !NOMINMAX
#endif // (defined(__WIN32__) || defined(WIN32))

#endif //!E3475__CONFIG_HPP__INCLUDED
