/*---------------------------------------------------------------------------*/
/*! @created   : 2005/05/10                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 5.0.0                                                       */
/*! @filename  : global.hpp                                                  */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's global entity       */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_GLOBAL_HPP__INCLUDED
#define E3475__HYDRA_GLOBAL_HPP__INCLUDED 500

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's global entity template                 //
//---------------------------------------------------------------------------//
template <
    typename HydraArgs
  , unsigned UniqueNumber>
struct hydra_global
{
    public:
        typedef HydraArgs                           args;
        typedef hydra_global<args, UniqueNumber>    selves;
        typedef hydra_range<args>                   range;
        typedef hydra_marrow<args>                  marrow;
        typedef hydra_viscera<args>                 viscera;
        typedef hydra_transformer<args>             transformer;
        typedef typename args::code_type            code_type;
        typedef typename args::value_type           value_type;
        typedef typename transformer::exception     exception;

    private:
        static const unsigned  unique_number_;      // unique number
        static transformer     transformer_;        // global transformer
        static value_type      default_read_radix_; // default reading radix
        static value_type      default_keep_radix_; // default keeping radix
        static code_type       default_sign_code_;  // default sign code
        static bool            default_sign_flag_;  // default sign flag

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : get unique number for "hydra" global entity    */
        /*------------------------------------------------------------*/
        static unsigned get_unique_number()
        {
            return selves::unique_number_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : set new transformer                            */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        static void set_transformer(
            const EtcContainer& src)
        {
            selves::transformer_ = src;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : get now transformer                            */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        static void get_transformer(
            EtcContainer&   src)
        {
            selves::transformer_.save(src);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : swap transformer                               */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        static void swap_transformer(
            EtcContainer&   src)
        {
            EtcContainer tm(src);
            selves::transformer_.save(src);
            selves::transformer_ = tm;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns result code of search for transfomer   */
        /*------------------------------------------------------------*/
        static code_type search_code(
            const value_type&   src)
        {
            return selves::transformer_.search_code(src);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns result value of search for transfomer  */
        /*------------------------------------------------------------*/
        static value_type search_vals(
            const code_type&    src)
        {
            return selves::transformer_.search_vals(src);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : set default reading radix value                */
        /*------------------------------------------------------------*/
        static void set_reading_radix(
            const value_type&   src) 
        {
            if (range::invalidity(src))
                exception::throws(exception::rash_radix_value);
            selves::default_read_radix_ = src;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : get default reading radix value                */
        /*------------------------------------------------------------*/
        static const value_type& get_reading_radix()
        {
            return selves::default_read_radix_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : set default keeping radix value                */
        /*------------------------------------------------------------*/
        static void set_keeping_radix(
            const value_type&   src)
        {
            if (range::invalidity(src))
                exception::throws(exception::rash_radix_value);
            selves::default_keep_radix_ = src;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : get default keeping radix value                */
        /*------------------------------------------------------------*/
        static const value_type& get_keeping_radix()
        {
            return selves::default_keep_radix_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : set default sign code value                    */
        /*------------------------------------------------------------*/
        static void set_sign_code(
            const code_type&    src)
        {
            selves::default_sign_code_ = src;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : get default sign code value                    */
        /*------------------------------------------------------------*/
        static const code_type& get_sign_code()
        {
            return selves::default_sign_code_;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : set default sign flag                          */
        /*------------------------------------------------------------*/
        static void set_sign_flag(
            const bool& src)
        {
            selves::default_sign_flag_ = src;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : get default sign flag                          */
        /*------------------------------------------------------------*/
        static const bool& get_sign_flag()
        {
            return selves::default_sign_flag_;
        }
};

/*------------------------------------------------------------*/
/*! @brief   : unique number for "hydra" global entity        */
/*------------------------------------------------------------*/
template <typename HydraArgs, unsigned UniqueNumber>
const unsigned 
hydra_global<HydraArgs, UniqueNumber>::unique_number_ = UniqueNumber;

/*------------------------------------------------------------*/
/*! @brief   : definition of global transformer               */
/*------------------------------------------------------------*/
template <typename HydraArgs, unsigned UniqueNumber> 
typename hydra_global<HydraArgs, UniqueNumber>::transformer 
hydra_global<HydraArgs, UniqueNumber>::transformer_;

/*------------------------------------------------------------*/
/*! @brief   : definition of default reading radix value      */
/*------------------------------------------------------------*/
template <typename HydraArgs, unsigned UniqueNumber> 
typename hydra_global<HydraArgs, UniqueNumber>::value_type 
hydra_global<HydraArgs, UniqueNumber>::default_read_radix_ = 10;

/*------------------------------------------------------------*/
/*! @brief   : definition of default keeping radix value      */
/*------------------------------------------------------------*/
template <typename HydraArgs, unsigned UniqueNumber> 
typename hydra_global<HydraArgs, UniqueNumber>::value_type 
hydra_global<HydraArgs, UniqueNumber>::default_keep_radix_ = range::max();

/*------------------------------------------------------------*/
/*! @brief   : definition of default sign code value          */
/*------------------------------------------------------------*/
template <typename HydraArgs, unsigned UniqueNumber> 
typename hydra_global<HydraArgs, UniqueNumber>::code_type 
hydra_global<HydraArgs, UniqueNumber>::default_sign_code_
 = static_cast<code_type>('-');

/*------------------------------------------------------------*/
/*! @brief   : definition of default sign flag                */
/*------------------------------------------------------------*/
template <typename HydraArgs, unsigned UniqueNumber> 
bool hydra_global<HydraArgs, UniqueNumber>::default_sign_flag_ = true;

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_GLOBAL_HPP__INCLUDED
