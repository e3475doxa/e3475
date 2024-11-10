/*---------------------------------------------------------------------------*/
/*! @created   : 2005/05/02                                                  */
/*! @update    : 2006/01/25                                                  */
/*! @version   : 5.0.0                                                       */
/*! @filename  : hydra.hpp                                                   */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : definitions for hydra as variable radix integer type        */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_HPP__INCLUDED
#define E3475__HYDRA_HPP__INCLUDED 500

//-----------------------//
// library configuration //
//-----------------------//
#include "config.hpp"

//------------------------------------//
// included standard libraries header //
//------------------------------------//
#include <set>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>

//---------------------------------//
// included boost libraries header //
//---------------------------------//
#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include <boost/operators.hpp>

//---------------------------------//
// included hydra libraries header //
//---------------------------------//
#include "hydra/args.hpp"
#include "hydra/range.hpp"
#include "hydra/marrow.hpp"
#include "hydra/viscera.hpp"
#include "hydra/exception.hpp"
#include "hydra/transformer.hpp"
#include "hydra/global.hpp"
#include "hydra/figure.hpp"
#include "hydra/operation.hpp"
#include "hydra/calculator.hpp"
#include "hydra/library.hpp"
#include "hydra/generator.hpp"

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------//
// variable type definitions //
//---------------------------//
typedef hydra_generator< hydra_library< hydra_global< hydra_args<char>,    0> > >   hydra;
typedef hydra_generator< hydra_library< hydra_global< hydra_args<wchar_t>, 0> > >  whydra;

//---------------------//
// finalized namespace //
//---------------------//
}}}

//-----------------------------------//
// e3475 hydra using namespace alias //
//-----------------------------------//
namespace e3475 {
    using details::hydra::hydra;
    using details::hydra::whydra;
}

#endif // !E3475__HYDRA_HPP__INCLUDED
