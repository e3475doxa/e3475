/*---------------------------------------------------------------------------*/
/*! @created   : 2004/10/07                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 7.0.0                                                       */
/*! @filename  : exception.hpp                                               */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2004-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's exception           */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_EXCEPTION_HPP__INCLUDED
#define E3475__HYDRA_EXCEPTION_HPP__INCLUDED 700

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// class : definition for hydra's exception template                         //
//---------------------------------------------------------------------------//
template <typename HydraArgs>
class hydra_exception : public HydraArgs::exception
{
    public:
        typedef HydraArgs                   args;
        typedef hydra_exception<args>       selves;

        typedef enum {
            details_unknown     = 0x00000000,
            rash_radix_value    = 0x00000001,
            not_found_vals      = 0x00000002,
            not_found_code      = 0x00000003,
            radix_different     = 0x00000004,
            calc_contradict     = 0x00000005,
            divide_by_zero      = 0x00000006,
            minus_exponent      = 0x00000007,
            minus_sqrt          = 0x00000008,
            over_digits         = 0x00000009,
        } details;

    protected:
        details  details_value_;    // kind of exception details

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : destructor                                     */
        /*------------------------------------------------------------*/
        virtual ~hydra_exception() throw() 
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : default constructor                            */
        /*------------------------------------------------------------*/
        hydra_exception() throw()
        : details_value_(selves::details_unknown)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor with details value                 */
        /*------------------------------------------------------------*/
        hydra_exception(
            const details&  kinds) throw()
        : details_value_(kinds)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : copy constructor                               */
        /*------------------------------------------------------------*/
        hydra_exception(
            const selves&   src) throw()
        : details_value_(src.details_value_)
        {
        }

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : returns message of exception details           */
        /*------------------------------------------------------------*/
        virtual const char* what() const throw()
        {
            switch (selves::values()) {
                case selves::rash_radix_value:
                    return "specified radix is rash value";
                case selves::not_found_vals:
                    return "search value is not found";
                case selves::not_found_code:
                    return "search code is not found";
                case selves::radix_different:
                    return "mutual radix value is different";
                case selves::calc_contradict:
                    return "occurrence of contradictory calculation";
                case selves::divide_by_zero:
                    return "zero divide occurs in quotient";
                case selves::minus_exponent:
                    return "minus exponent is not supported";
                case selves::minus_sqrt:
                    return "minus sqrt is not supported";
                case selves::over_digits:
                    return "digits of calculator started overflow";
                case selves::details_unknown:
                default:
                    return "unknown exception details";
            }
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns details value of "hydra" exception     */
        /*------------------------------------------------------------*/
        virtual const details& values() const throw()
        {
            return selves::details_value_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitutions                                  */
        /*------------------------------------------------------------*/
        virtual selves&  operator=(
            const selves&   src) throw()
        {
            selves::details_value_ = src.details_value_;
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : operator equal                                 */
        /*------------------------------------------------------------*/
        virtual bool operator==(
            const selves&   src) const throw()
        {
            return (selves::values() == src.values()) ? true : false;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : operator not equals                            */
        /*------------------------------------------------------------*/
        virtual bool operator!=(
            const selves&   src) const throw()
        {
            return !(*this == src);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : unification of selves throw                    */
        /*------------------------------------------------------------*/
        static void throws(
            const details&  kinds)
        {
            throw selves(kinds);
        }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_EXCEPTION_HPP__INCLUDED
