/*---------------------------------------------------------------------------*/
/*! @created   : 2004/10/02                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 7.0.0                                                       */
/*! @filename  : transformer.hpp                                             */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2004-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's transformer         */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_TRANSFORMER_HPP__INCLUDED
#define E3475__HYDRA_TRANSFORMER_HPP__INCLUDED 700

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's hydra's sort code template             //
//---------------------------------------------------------------------------//
template <typename PtrPairType>
struct hydra_trans_less_code :
    public std::binary_function<PtrPairType, PtrPairType, bool>
{
    typedef hydra_trans_less_code<PtrPairType>      selves;
    typedef typename selves::result_type            result_type;
    typedef typename selves::first_argument_type    first_argument_type;
    typedef typename selves::second_argument_type   second_argument_type;

    /*------------------------------------------------------------*/
    /*! @brief   : judges less than second object of argument     */
    /*------------------------------------------------------------*/
    result_type operator() (
        const first_argument_type&  lhs
      , const second_argument_type& rhs) const
    {
        return lhs->second < rhs->second;
    }
};

//---------------------------------------------------------------------------//
// structure : definition for hydra's hydra's sort value template            //
//---------------------------------------------------------------------------//
template <typename PtrPairType>
struct hydra_trans_less_vals :
    public std::binary_function<PtrPairType, PtrPairType, bool>
{
    typedef hydra_trans_less_vals<PtrPairType>      selves;
    typedef typename selves::result_type            result_type;
    typedef typename selves::first_argument_type    first_argument_type;
    typedef typename selves::second_argument_type   second_argument_type;

    /*------------------------------------------------------------*/
    /*! @brief   : judges less than first object of argument      */
    /*------------------------------------------------------------*/
    result_type operator() (
        const first_argument_type&  lhs
      , const second_argument_type& rhs) const
    {
        return lhs->first < rhs->first;
    }
};

//---------------------------------------------------------------------------//
// structure : definition for hydra's hydra's transformer template           //
//---------------------------------------------------------------------------//
template <typename HydraArgs>
class hydra_transformer
{
    public:
        typedef HydraArgs                                                args;
        typedef hydra_transformer<args>                                  selves;
        typedef hydra_exception<args>                                    exception;
        typedef typename args::code_type                                 code_type;
        typedef typename args::value_type                                value_type;
        typedef typename args::allocator_type                            core_alloc;
        typedef std::pair<value_type, code_type>                         trans_pair;
        typedef typename core_alloc::template rebind<trans_pair>::other  trans_alloc;
        typedef typename core_alloc::template rebind<trans_pair*>::other terms_alloc;
        typedef hydra_trans_less_vals<trans_pair*>                       less_vals;
        typedef hydra_trans_less_code<trans_pair*>                       less_code;
        typedef std::vector<trans_pair, trans_alloc>                     trans_core;
        typedef std::set<trans_pair*, less_vals, terms_alloc>            trans_vals;
        typedef std::set<trans_pair*, less_code, terms_alloc>            trans_code;

    private:
        trans_core     core_;     // main transformer container
        trans_vals     vals_;     // sub transformer container for value
        trans_code     code_;     // sub transformer container for code

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : destructor                                     */
        /*------------------------------------------------------------*/
        ~hydra_transformer() throw()
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : default constructor                            */
        /*------------------------------------------------------------*/
        hydra_transformer()
        {
            selves::core_.resize(16);
            selves::core_[ 0] = trans_pair( 0, '0');
            selves::core_[ 1] = trans_pair( 1, '1');
            selves::core_[ 2] = trans_pair( 2, '2');
            selves::core_[ 3] = trans_pair( 3, '3');
            selves::core_[ 4] = trans_pair( 4, '4');
            selves::core_[ 5] = trans_pair( 5, '5');
            selves::core_[ 6] = trans_pair( 6, '6');
            selves::core_[ 7] = trans_pair( 7, '7');
            selves::core_[ 8] = trans_pair( 8, '8');
            selves::core_[ 9] = trans_pair( 9, '9');
            selves::core_[10] = trans_pair(10, 'A');
            selves::core_[11] = trans_pair(11, 'B');
            selves::core_[12] = trans_pair(12, 'C');
            selves::core_[13] = trans_pair(13, 'D');
            selves::core_[14] = trans_pair(14, 'E');
            selves::core_[15] = trans_pair(15, 'F');
            selves::initialize();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : copy constructor                               */
        /*------------------------------------------------------------*/
        hydra_transformer(
            const selves&   src)
        : core_(src.core_.begin(), src.core_.end())
        , vals_(src.vals_.begin(), src.vals_.end())
        , code_(src.code_.begin(), src.code_.end())
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for etceteras container            */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        hydra_transformer(
            const EtcContainer& src)
        : core_(src.begin(), src.end())
        {
            selves::initialize();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for container's iterator           */
        /*------------------------------------------------------------*/
        template <typename InputIterator>
        hydra_transformer(
            InputIterator     first
          , InputIterator     last)
        : core_(first, last)
        {
            selves::initialize();
        }

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : save transformer values                        */
        /*------------------------------------------------------------*/
        void save(
            selves& src)
        {
            src = *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : save transformer values to etceteras container */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        void save(
            EtcContainer&   src)
        {
            EtcContainer(selves::core_.begin(), selves::core_.end()).swap(src);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : erases values and copies specified iterator    */
        /*------------------------------------------------------------*/
        template <typename InputIterator>
        void assign(
            InputIterator     first,
            InputIterator     last)
        {
            selves::core_.assign(first, last);
            selves::initialize();
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns result code of search for transfomer   */
        /*------------------------------------------------------------*/
        code_type search_code(
            const value_type& value) const
        {
            trans_pair search(value, 0);
            typedef typename trans_vals::const_iterator trans_vals_itr;
            trans_vals_itr result = selves::vals_.lower_bound(&search);
            if (result == selves::vals_.end()) 
                exception::throws(exception::not_found_code);
            return (*result)->second;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns result value of search for transfomer  */
        /*------------------------------------------------------------*/
        value_type search_vals(
            const code_type& code) const
        {
            trans_pair search(0, code);
            typedef typename trans_code::const_iterator trans_code_itr;
            trans_code_itr result = selves::code_.lower_bound(&search);
            if (result == selves::code_.end()) 
                exception::throws(exception::not_found_vals);
            return (*result)->first;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitutions                                  */
        /*------------------------------------------------------------*/
        selves& operator=(
            const selves&   src)
        {
            selves::assign(src.core_.begin(), src.core_.end());
            return *this;
        }

    private:
        /*------------------------------------------------------------*/
        /*! @brief   : initialize sub transformer                     */
        /*------------------------------------------------------------*/
        void initialize()
        {
            selves::code_.clear();
            selves::vals_.clear();
            std::for_each(selves::core_.begin(), selves::core_.end(),
                boost::bind(boost::mem_fn(&selves::section), this, _1));
        }

        /*------------------------------------------------------------*/
        /*! @brief   : initialize sub transformer at for_each section */
        /*------------------------------------------------------------*/
        void section(
            trans_pair& item)
        {
            selves::code_.insert(&item);
            selves::vals_.insert(&item);
        }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_TRANSFORMER_HPP__INCLUDED
