/*---------------------------------------------------------------------------*/
/*! @created   : 2005/04/28                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 6.0.0                                                       */
/*! @filename  : library.hpp                                                 */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's library             */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_LIBRARY_HPP__INCLUDED
#define E3475__HYDRA_LIBRARY_HPP__INCLUDED 600

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's library template                       //
//---------------------------------------------------------------------------//
template <typename HydraGlobals>
struct hydra_library
{
    typedef HydraGlobals                        global;
    typedef hydra_library<global>               selves;
    typedef hydra_calculator<global>            calc;
    typedef hydra_figure<global>                figure;
    typedef typename global::args               args;
    typedef typename global::range              range;
    typedef typename global::exception          exception;
    typedef typename args::container            container;
    typedef typename args::code_type            code_type;
    typedef typename args::value_type           value_type;
    typedef typename args::digit_type           digit_type;

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from code arrangement       */
    /*------------------------------------------------------------*/
    static void initialize(
        figure&             src
      , code_type*          ary
      , const value_type&   read = global::get_reading_radix()
      , const value_type&   keep = global::get_keeping_radix())
    {
        selves::initialize(src, static_cast<const code_type*>(ary), read, keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from const code arrangement */
    /*------------------------------------------------------------*/
    static void initialize(
        figure&             src
      , const code_type*    ary
      , const value_type&   read = global::get_reading_radix()
      , const value_type&   keep = global::get_keeping_radix())
    {
        const code_type* ends  = ary;
        while (*ends++);
        if (ary == --ends) return;
        selves::initialize(src, ary, ends, read, keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from code range             */
    /*------------------------------------------------------------*/
    static void initialize(
        figure&             src
      , code_type*          first
      , code_type*          last
      , const value_type&   read = global::get_reading_radix()
      , const value_type&   keep = global::get_keeping_radix())
    {
        selves::initialize(
                     src
                   , static_cast<const code_type*>(first)
                   , static_cast<const code_type*>(last)
                   , read
                   , keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from const code range       */
    /*------------------------------------------------------------*/
    static void initialize(
        figure&             src
      , const code_type*    first
      , const code_type*    last
      , const value_type&   read = global::get_reading_radix()
      , const value_type&   keep = global::get_keeping_radix())
    {
        std::reverse_iterator<const code_type*> ib(last);
        std::reverse_iterator<const code_type*> ie(first);
        selves::initialize(src, ib, ie, read, keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from etceteras container    */
    /*------------------------------------------------------------*/
    template <typename EtcContainer>
    static void initialize(
        figure&                 src
      , const EtcContainer&     value
      , const value_type&       read = global::get_reading_radix()
      , const value_type&       keep = global::get_keeping_radix())
    {
        selves::initialize(src, value.rbegin(), value.rend(), read, keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from etceteras container    */
    /*------------------------------------------------------------*/
    template <typename EtcContainer>
    static void initialize(
        figure&                 src
      , const bool&             sign
      , const EtcContainer&     value
      , const value_type&       read = global::get_reading_radix()
      , const value_type&       keep = global::get_keeping_radix())
    {
        selves::initialize(src, sign, value.rbegin(), value.rend(), read, keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from arrangement range      */
    /*------------------------------------------------------------*/
    template <typename ReverseIterator>
    static void initialize(
        figure&                 src
      , const ReverseIterator&  first
      , const ReverseIterator&  last
      , const value_type&       read = global::get_reading_radix()
      , const value_type&       keep = global::get_keeping_radix())
    {
          ReverseIterator tmp(last);
          bool sign = (*last.base() != global::get_sign_code());
          if (!sign) --tmp;
          selves::initialize(src, sign, first, tmp, read, keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : initializes figure from arrangement range      */
    /*------------------------------------------------------------*/
    template <typename ReverseIterator>
    static void initialize(
        figure&                 src
      , const bool&             sign
      , const ReverseIterator&  first
      , const ReverseIterator&  last
      , const value_type&       read = global::get_reading_radix()
      , const value_type&       keep = global::get_keeping_radix())
    {
        src.set_sign_flag(sign);
        src.figure::set_radix_value(read);
        src.resize(std::distance(first, last));
        std::transform(first, last, src.begin(), global::search_vals);
        calc::cut_front_zero(src);
        selves::change(src, src, keep);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : returns etceteras container with finalizes     */
    /*------------------------------------------------------------*/
    template <typename EtcContainer>
    static EtcContainer finalize(
        const figure&       src
      , const value_type&   radix = global::get_reading_radix())
    {
        EtcContainer value;
        selves::finalize(src, value, radix);
        return value;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : finalizes figure for etceteras container       */
    /*------------------------------------------------------------*/
    template <typename EtcContainer>
    static void finalize(
        const figure&       src
      , EtcContainer&       value
      , const value_type&   radix = global::get_reading_radix())
    {
        figure tmp;
        selves::change(tmp, src, radix);
        if (tmp.size() == 0) {
            value.resize(1);
            *value.begin() = global::search_code(0);
            return;
        }

        value.resize(tmp.size() + (tmp.get_sign_flag() ? 0 : 1));
        typename EtcContainer::iterator itr = value.begin();
        if (!tmp.get_sign_flag()) *itr++ = global::get_sign_code();
        std::transform(tmp.rbegin(), tmp.rend(), itr, global::search_code);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : comparisons equal A B (A == B)                 */
    /*------------------------------------------------------------*/
    static bool equals(
        const figure&   A
      , const figure&   B)
    {
        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container lhs(A), rhs(B);
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);

        if (!lhs.size() || !rhs.size()) 
           return (lhs.size() == rhs.size()) ? true : false;
        if (A.get_sign_flag() != B.get_sign_flag()) return false;
        return calc::equals(lhs, rhs);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : comparisons less A B (A < B)                   */
    /*------------------------------------------------------------*/
    static bool less(
        const figure&   A
      , const figure&   B)
    {
        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container lhs(A), rhs(B);
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);

        if (A.get_sign_flag() != B.get_sign_flag()) 
            if (!lhs.size() || !rhs.size()) 
                if (lhs.size() == rhs.size()) return false;
                else return (A.get_sign_flag()) ? false : true;
            else return (A.get_sign_flag()) ? false : true;
        return A.get_sign_flag() == calc::less(lhs, rhs, A.get_sign_flag());
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations plus A B (A + B)                    */
    /*------------------------------------------------------------*/
    static void plus(
        figure&         src
      , const figure&   A
      , const figure&   B)
    {
        if (A.get_sign_flag() != B.get_sign_flag()) {
            if (A.get_sign_flag()) 
                selves::minus(src, A,
                    figure(B, !B.get_sign_flag(),
                           A.get_radix_value()));
            else selves::minus(src, B,
                    figure(A, !A.get_sign_flag(),
                           A.get_radix_value()));
            return;
        }

        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container         lhs(A), rhs(B);
        const value_type& radix = A.get_radix_value();
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);
        digit_type digits = std::max(lhs.size(), rhs.size());

        calc::plus(src, radix
                 , calc::fill_front_zero(lhs, digits)
                 , calc::fill_front_zero(rhs, digits));
        src.set_sign_flag(A.get_sign_flag());
        src.figure::set_radix_value(radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations minus A B (A - B)                   */
    /*------------------------------------------------------------*/
    static void minus(
        figure&         src
      , const figure&   A
      , const figure&   B)
    {
        if (!B.get_sign_flag()
          || (A.get_sign_flag() != B.get_sign_flag())) {
            selves::plus(src, A,
                    figure(B, !B.get_sign_flag(),
                           A.get_radix_value()));
            return;
        }

        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container         lhs(A), rhs(B);
        const value_type& radix = A.get_radix_value();
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);
        digit_type digits = std::max(lhs.size(), rhs.size());
        bool       less   = calc::less(lhs, rhs, A.get_sign_flag());
        if (less) lhs.swap(rhs);

        calc::minus(src, radix,
                    calc::fill_front_zero(lhs, digits),
                    calc::fill_front_zero(rhs, digits));
        src.set_sign_flag(!less);
        src.figure::set_radix_value(radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations multiply A B (A * B)                */
    /*------------------------------------------------------------*/
    static void multiply(
        figure&         src
      , const figure&   A
      , const figure&   B)
    {
        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container         lhs(A), rhs(B);
        const value_type& radix = A.get_radix_value();
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);

        calc::multiply(src, radix, lhs, rhs);
        src.set_sign_flag(A.get_sign_flag() == B.get_sign_flag());
        src.figure::set_radix_value(radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations quotient A B (A / B)                */
    /*------------------------------------------------------------*/
    static void quotient(
        figure&         src
      , const figure&   A
      , const figure&   B)
    {
        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container         lhs(A), rhs(B);
        const value_type& radix = A.get_radix_value();
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);

        if (!rhs.size()) exception::throws(exception::divide_by_zero);
        if (lhs.size() < rhs.size()) src.clear();
        else calc::quotient(src, radix, lhs, rhs);
        src.set_sign_flag(A.get_sign_flag() == B.get_sign_flag());
        src.figure::set_radix_value(radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations remain A B (A % B)                  */
    /*------------------------------------------------------------*/
    static void remainder(
        figure&         src
      , const figure&   A
      , const figure&   B)
    {
        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container         lhs(A), rhs(B);
        const value_type& radix = A.get_radix_value();
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);

        if (!rhs.size()) exception::throws(exception::divide_by_zero);
        if (lhs.size() < rhs.size()) lhs.swap(src);
        else calc::remainder(src, radix, lhs, rhs);
        src.set_sign_flag(A.get_sign_flag());
        src.figure::set_radix_value(radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : increment                                      */
    /*------------------------------------------------------------*/
    static void increment(
        figure&     src)
    {
        calc::cut_front_zero(src);

        if (!src.size()) {
            src.resize(1);
            src.set_sign_flag(true);
            calc::increment(src, src.get_radix_value());
        } else {
            if (src.get_sign_flag()) {
                src.resize(src.size() + 1);
                calc::increment(src, src.get_radix_value());
            } else calc::decrement(src, src.get_radix_value());
        }
    }

    /*------------------------------------------------------------*/
    /*! @brief   : decrement                                      */
    /*------------------------------------------------------------*/
    static void decrement(
        figure&     src)
    {
        calc::cut_front_zero(src);

        if (!src.size()) {
            src.resize(1);
            src.set_sign_flag(false);
            calc::increment(src, src.get_radix_value());
        } else {
            if (src.get_sign_flag())
                calc::decrement(src, src.get_radix_value());
            else {
                src.resize(src.size() + 1);
                calc::increment(src, src.get_radix_value());
            }
        }
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations exponent A B (A ^ B)                */
    /*------------------------------------------------------------*/
    static void exponent(
        figure&         src
      , const figure&   A
      , const figure&   B)
    {
        if (!B.get_sign_flag())
            exception::throws(exception::minus_exponent);
        if (A.get_radix_value() != B.get_radix_value())
            exception::throws(exception::radix_different);

        container         lhs(A), rhs(B);
        const value_type& radix = A.get_radix_value();
        calc::cut_front_zero(lhs);
        calc::cut_front_zero(rhs);

        bool odd = calc::exponent(src, radix, lhs, rhs);
        src.set_sign_flag(A.get_sign_flag() ? true : odd);
        src.figure::set_radix_value(radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations sqrt                                */
    /*------------------------------------------------------------*/
    static bool sqrt(
        figure&         src
      , const figure&   target)
    {
        if (!target.get_sign_flag())
            exception::throws(exception::minus_sqrt);

        container         tmp(target);
        const value_type& radix = target.get_radix_value();
        calc::cut_front_zero(tmp);

        src.figure::set_radix_value(radix);
        src.set_sign_flag(target.get_sign_flag());
        return calc::sqrt(src, radix, tmp);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : returns new figure with change radix value     */
    /*------------------------------------------------------------*/
    static figure change(
        const figure&       target
      , const value_type&   radix)
    {
        figure    src;
        container tmp(target);
        calc::cut_front_zero(tmp);

        calc::change(src, tmp, target.get_radix_value(), radix);
        src.set_sign_flag(target.get_sign_flag());
        src.figure::set_radix_value(radix);
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : change radix value                             */
    /*------------------------------------------------------------*/
    static void change(
        figure&             src
      , const figure&       target
      , const value_type&   radix)
    {
        container tmp(target);
        calc::cut_front_zero(tmp);

        calc::change(src, tmp, target.get_radix_value(), radix);
        src.set_sign_flag(target.get_sign_flag());
        src.figure::set_radix_value(radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : return etceteras container which changed radix */
    /*------------------------------------------------------------*/
    template <typename EtcContainer>
    static EtcContainer change(
        const EtcContainer& value
      , const value_type&   base
      , const value_type&   change)
    {
        figure tmp;
        selves::initialize(tmp, value, base, change);
        return selves::finalize<EtcContainer>(tmp, change);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : return etceteras container which changed radix */
    /*------------------------------------------------------------*/
    template <typename EtcContainer1, typename EtcContainer2>
    static EtcContainer1 change(
        const EtcContainer2&    value
      , const value_type&       base
      , const value_type&       change)
    {
        figure tmp;
        selves::initialize(tmp, value, base, change);
        return selves::finalize<EtcContainer1>(tmp, change);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : return etceteras container which changed radix */
    /*------------------------------------------------------------*/
    template <typename EtcContainer, typename InputIterator>
    static EtcContainer change(
        const InputIterator&    first
      , const InputIterator&    last
      , const value_type&       base
      , const value_type&       change)
    {
        figure tmp;
        selves::initialize(tmp, first, last, base, change);
        return selves::finalize<EtcContainer>(tmp, change);
    }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_LIBRARY_HPP__INCLUDED
