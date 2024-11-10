/*---------------------------------------------------------------------------*/
/*! @created   : 2004/12/07                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 7.0.0                                                       */
/*! @filename  : generator.hpp                                               */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2004-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's generator           */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_GENERATOR_HPP__INCLUDED
#define E3475__HYDRA_GENERATOR_HPP__INCLUDED 700

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// class : definition for hydra's generator template                         //
//---------------------------------------------------------------------------//
template <typename HydraLibrary>
class hydra_generator : public HydraLibrary::figure
  , private boost::unit_steppable<     hydra_generator< HydraLibrary > >
  , private boost::totally_ordered<    hydra_generator< HydraLibrary > >
  , private boost::integer_arithmetic< hydra_generator< HydraLibrary > >
{
    public:
        typedef HydraLibrary                            lib;
        typedef hydra_generator<lib>                    selves;
        typedef typename lib::args                      args;
        typedef typename lib::range                     range;
        typedef typename lib::global                    global;
        typedef typename lib::figure                    figure;
        typedef typename global::marrow                 marrow;
        typedef typename global::viscera                viscera;
        typedef typename global::exception              exception;
        typedef typename global::transformer            transformer;
        typedef typename args::primitive                primitive;
        typedef typename args::container                container;
        typedef typename args::size_type                size_type;
        typedef typename args::code_type                code_type;
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

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : destructor                                     */
        /*------------------------------------------------------------*/
        virtual ~hydra_generator() throw()
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : default constructor                            */
        /*------------------------------------------------------------*/
        explicit hydra_generator(
            const allocator_type&   allloc = allocator_type())
        : figure(allloc)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : copy constructor                               */
        /*------------------------------------------------------------*/
        hydra_generator(
            const selves&   src)
        : figure(src)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for marrow container               */
        /*------------------------------------------------------------*/
        hydra_generator(
            const marrow&  src)
        : figure(src)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for marrow container with parameter*/
        /*------------------------------------------------------------*/
        explicit hydra_generator(
            const marrow&  src
          , const bool&    sign)
        : figure(src, sign)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for primitive type                 */
        /*------------------------------------------------------------*/
        hydra_generator(
            const primitive&        src
          , const value_type&       keep  = global::get_keeping_radix()
          , const allocator_type&   alloc = allocator_type())
        : figure(src >= primitive(0), (src < primitive(0)) ? -src : src, keep, alloc)
        {
        }

        /*------------------------------------------------------------*/
        /*! @brief   : designate digits and values constructor        */
        /*------------------------------------------------------------*/
        explicit hydra_generator(
            const digit_type&       digit
          , const code_type&        code
          , const bool&             sign
          , const value_type&       read
          , const value_type&       keep  = global::get_keeping_radix()
          , const allocator_type&   alloc = allocator_type())
        : figure(digit, global::search_vals(code), sign, read, alloc)
        {
            lib::change(*this, *this, keep);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for etceteras container            */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        hydra_generator(
            const EtcContainer&     src
          , const value_type&       read  = global::get_reading_radix()
          , const value_type&       keep  = global::get_keeping_radix()
          , const allocator_type&   alloc = allocator_type()) 
        : figure(alloc)
        {
            selves::initialize(src, read, keep);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : constructor for etc container's iterator       */
        /*------------------------------------------------------------*/
        template <typename InputIterator>
        explicit hydra_generator(
            const InputIterator&    first
          , const InputIterator&    last
          , const value_type&       read  = global::get_reading_radix()
          , const value_type&       keep  = global::get_keeping_radix()
          , const allocator_type&   alloc = allocator_type())
        : figure(alloc)
        {
            selves::initialize(first, last, read, keep);
        }

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : set new radix value                            */
        /*------------------------------------------------------------*/
        void set_radix_value(
            const value_type&   radix)
        {
            lib::change(*this, *this, radix);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : initializes hydra                              */
        /*------------------------------------------------------------*/
        void initialize(
            const digit_type&   digit
          , const code_type&    code
          , const bool&         sign
          , const value_type&   read
          , const value_type&   keep  = global::get_keeping_radix())
        {
            selves::assign(digit, global::search_vals(code), sign, read);
            lib::change(*this, *this, keep);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : initializes hydra for etceteras container      */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        void initialize(
            const EtcContainer& src
          , const value_type&   read  = global::get_reading_radix()
          , const value_type&   keep  = global::get_keeping_radix())
        {
            lib::initialize(*this, src, read, keep);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : initializes hydra for etc container's iterator */
        /*------------------------------------------------------------*/
        template <typename InputIterator>
        void initialize(
            const InputIterator&    first
          , const InputIterator&    last
          , const value_type&       read  = global::get_reading_radix()
          , const value_type&       keep  = global::get_keeping_radix())
        {
            lib::initialize(*this, first, last, read, keep);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : returns etceteras container with finalizes     */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        EtcContainer finalize(
            const value_type&   radix = global::get_reading_radix())
        {
            EtcContainer  value;
            return selves::finalize(value, radix);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : finalizes hydra for etceteras container        */
        /*------------------------------------------------------------*/
        template <typename EtcContainer>
        EtcContainer& finalize(
            EtcContainer&       value,
            const value_type&   radix = global::get_reading_radix())
        {
            lib::finalize(*this, value, radix);
            return value;
        }

    public:
        /*------------------------------------------------------------*/
        /*! @brief   : substitutions                                  */
        /*------------------------------------------------------------*/
        selves& operator= (
            const selves&   src)
        {
            figure::operator=(src);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : operations equals                              */
        /*------------------------------------------------------------*/
        bool operator==(
            const selves&   src) const
        {
            if (selves::get_radix_value() != src.get_radix_value())
                return lib::equals(*this, lib::change(src, selves::get_radix_value()));
            else return lib::equals(*this, src);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : operations less                                */
        /*------------------------------------------------------------*/
        bool operator< (
            const selves&   src) const
        {
            if (selves::get_radix_value() != src.get_radix_value())
                return lib::less(*this, lib::change(src, selves::get_radix_value()));
            else return lib::less(*this, src);
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitution plus                              */
        /*------------------------------------------------------------*/
        selves& operator+=(
            const selves&   src)
        {
            if (selves::get_radix_value() != src.get_radix_value())
                lib::plus(*this, *this, lib::change(src, selves::get_radix_value()));
            else lib::plus(*this, *this, src);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitution minus                             */
        /*------------------------------------------------------------*/
        selves& operator-=(
            const selves&   src)
        {
            if (selves::get_radix_value() != src.get_radix_value())
                lib::minus(*this, *this, lib::change(src, selves::get_radix_value()));
            else lib::minus(*this, *this, src);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitution multiply                          */
        /*------------------------------------------------------------*/
        selves& operator*=(
            const selves&   src)
        {
            if (selves::get_radix_value() != src.get_radix_value())
                lib::multiply(*this, *this, lib::change(src, selves::get_radix_value()));
            else lib::multiply(*this, *this, src);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitution quotient                          */
        /*------------------------------------------------------------*/
        selves& operator/=(
            const selves&   src)
        {
            if (selves::get_radix_value() != src.get_radix_value())
                lib::quotient(*this, *this, lib::change(src, selves::get_radix_value()));
            else lib::quotient(*this, *this, src);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : substitution remain                            */
        /*------------------------------------------------------------*/
        selves& operator%=(
            const selves&   src)
        {
            if (selves::get_radix_value() != src.get_radix_value())
                lib::remainder(*this, *this, lib::change(src, selves::get_radix_value()));
            else lib::remainder(*this, *this, src);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : increment                                      */
        /*------------------------------------------------------------*/
        selves& operator++()
        {
            lib::increment(*this);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : decrement                                      */
        /*------------------------------------------------------------*/
        selves& operator--()
        {
            lib::decrement(*this);
            return *this;
        }

        /*------------------------------------------------------------*/
        /*! @brief   : sign reverse                                   */
        /*------------------------------------------------------------*/
        selves operator- () const
        {
            return selves(
                static_cast<const marrow&>(*this), !selves::get_sign_flag());
        }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_GENERATOR_HPP__INCLUDED
