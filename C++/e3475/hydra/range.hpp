/*---------------------------------------------------------------------------*/
/*! @created   : 2005/05/10                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 4.0.0                                                       */
/*! @filename  : range.hpp                                                   */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's heads range         */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_RANGE_HPP__INCLUDED
#define E3475__HYDRA_RANGE_HPP__INCLUDED 400

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's heads range template                   //
//---------------------------------------------------------------------------//
template <typename HydraArgs>
struct hydra_range : 
    public std::unary_function<typename HydraArgs::value_type, bool>
{
    typedef HydraArgs                           args;
    typedef hydra_range<args>                   selves;
    typedef typename selves::result_type        result_type;
    typedef typename selves::argument_type      argument_type;

    /*------------------------------------------------------------*/
    /*! @brief   : effective judging of specification value       */
    /*------------------------------------------------------------*/
    result_type operator() (
        const argument_type& value)
    {
        if (value < selves::min()) return false;
        if (value > selves::max()) return false;
        return true;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : invalid judging of specification value         */
    /*------------------------------------------------------------*/
    static result_type invalidity(
        const argument_type& value)
    {
        return !selves()(value);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : returns value of min at hydra heads            */
    /*------------------------------------------------------------*/
    static const argument_type& min()
    {
        static const argument_type minimum = 2;
        return minimum;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : returns value of min at hydra heads            */
    /*------------------------------------------------------------*/
    static const argument_type& max()
    {
        static const argument_type maximum = 
                    static_cast<argument_type>(
                        std::sqrt(static_cast<double>(
                            argument_type(~argument_type()))) + 1);
        return maximum;
    }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_RANGE_HPP__INCLUDED
