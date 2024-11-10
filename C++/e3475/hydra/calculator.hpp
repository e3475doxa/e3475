/*---------------------------------------------------------------------------*/
/*! @created   : 2005/04/28                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 6.0.0                                                       */
/*! @filename  : calculator.hpp                                              */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's calculator          */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_CALCULATOR_HPP__INCLUDED
#define E3475__HYDRA_CALCULATOR_HPP__INCLUDED 600

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's calculator template                    //
//---------------------------------------------------------------------------//
template <typename HydraGlobals>
struct hydra_calculator
{
    typedef HydraGlobals                            global;
    typedef hydra_calculator<global>                selves;
    typedef hydra_operation<global>                 operation;
    typedef typename global::args                   args;
    typedef typename global::range                  range;
    typedef typename global::exception              exception;
    typedef typename args::container                container;
    typedef typename args::value_type               value_type;
    typedef typename args::digit_type               digit_type;
    typedef typename args::iterator                 iterator;
    typedef typename args::const_iterator           const_iterator;
    typedef typename args::reverse_iterator         reverse_iterator;
    typedef typename args::const_reverse_iterator   const_reverse_iterator;

    /*------------------------------------------------------------*/
    /*! @brief   : check over digits                              */
    /*------------------------------------------------------------*/
    static digit_type check_over_digit(
        const digit_type&   A
      , const digit_type&   B
      , const bool&         plus = true)
    {
        digit_type result = plus  ? A + B : A * B;
        if (result < A || result < B)
            exception::throws(exception::over_digits);
        return result;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : filling front area with zero                   */
    /*------------------------------------------------------------*/
    static container& fill_front_zero(
        container&          src
      , const digit_type&   digit)
    {
        if (digit <= src.size()) return src;
        return operation::fill_front_zero(src, digit);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : cutting front area with zero                   */
    /*------------------------------------------------------------*/
    static container& cut_front_zero(
        container&      src)
    {
        return operation::cut_front_zero(src);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : comparisons equal A B (A == B)                 */
    /*------------------------------------------------------------*/
    static bool equals(
        const container&    A
      , const container&    B)
    {
        if (A.size() != B.size()) return false;
        return operation::equals(A, B);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : comparisons less A B (A < B)                   */
    /*------------------------------------------------------------*/
    static bool less(
        const container&    A
      , const container&    B
      , const bool&         charm = true)
    {
        if (A.size() != B.size()) 
            return (A.size() < B.size()) ? true : false;
        return operation::less(A, B, charm);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations plus A B (A + B)                    */
    /*------------------------------------------------------------*/
    static container& plus(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        container buffer(selves::check_over_digit(A.size(), 1));
        operation::plus(buffer, radix, A, B);
        src.swap(operation::cut_front_zero(buffer));
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations minus A B (A - B)                   */
    /*------------------------------------------------------------*/
    static container& minus(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        container buffer(A.size());
        operation::minus(buffer, radix, A, B);
        src.swap(operation::cut_front_zero(buffer));
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations multiply A B (A * B)                */
    /*------------------------------------------------------------*/
    static container& multiply(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        container buffer(selves::check_over_digit(A.size(), B.size()));
        if (B.size() == 1) {
            value_type tmp = *B.begin();
            operation::multiply_single(buffer, radix, A, tmp);
        } else {
            container process(buffer.size());
            operation::multiply_any(buffer, process, radix, A, B);
        }
        src.swap(operation::cut_front_zero(buffer));
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations quotient A B (A / B)                */
    /*------------------------------------------------------------*/
    static container& quotient(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        if (B.size() == 1) {
            container  quotient(A.size());
            value_type remainder = 0;
            value_type divisor   = *B.begin();
            operation::quotient_single(quotient, remainder, radix, A, divisor);
            src.swap(operation::cut_front_zero(quotient));
        } else {
            container quotient(A.size());
            container divisor(selves::check_over_digit(B.size(), 1));
            container remainder(selves::check_over_digit(B.size(), 1));
            std::copy(B.begin(), B.end(), divisor.begin());
            operation::quotient_any(quotient, remainder, radix, A, divisor);
            src.swap(operation::cut_front_zero(quotient));
        }
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations remain A B (A % B)                  */
    /*------------------------------------------------------------*/
    static container& remainder(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        if (B.size() == 1) {
            container  quotient(A.size());
            value_type remainder = 0;
            value_type divisor   = *B.begin();
            operation::quotient_single(quotient, remainder, radix, A, divisor);
            if (remainder) {
                src.resize(1);
                *src.begin() = remainder;
            } else src.clear();
        } else {
            container quotient(A.size());
            container divisor(selves::check_over_digit(B.size(), 1));
            container remainder(selves::check_over_digit(B.size(), 1));
            std::copy(B.begin(), B.end(), divisor.begin());
            operation::quotient_any(quotient, remainder, radix, A, divisor);
            src.swap(operation::cut_front_zero(remainder));
        }
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : increment                                      */
    /*------------------------------------------------------------*/
    static void increment(
        container&          src
      , const value_type&   radix)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        iterator ib = src.begin();
        *ib += 1;
        while (*ib == radix) {
            *ib = 0;
            ++ib;
            *ib += 1;
        }
        operation::cut_front_zero(src);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : decrement                                      */
    /*------------------------------------------------------------*/
    static void decrement(
        container&          src
      , const value_type&   radix)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        iterator ie = src.end();
        iterator ib = src.begin();
        for (; ib != ie; ++ib) {
            if (*ib) break;
            *ib = radix - 1;
        }
        *ib -= 1;
        operation::cut_front_zero(src);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations exponent A B (A ^ B)                */
    /*------------------------------------------------------------*/
    static bool exponent(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        bool odd = false;
        if (!B.size()) {
            src.resize(1);
            *src.begin() = 1;
        } else {
            container process(A);
            container counter(B);
            selves::decrement(counter, radix);
            for (; counter.size(); odd = !odd, selves::decrement(counter, radix))
                selves::multiply(process, radix, process, A);
            src.swap(process);
        }
        operation::cut_front_zero(src);
        return odd;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations sqrt                                */
    /*------------------------------------------------------------*/
    static bool sqrt(
        container&          src
      , const value_type&   radix
      , const container&    target)
    {
        if (range::invalidity(radix))
            exception::throws(exception::rash_radix_value);

        if (!target.size()) {
            src.clear();
            return true;
        }

        bool       just = true;
        value_type remain_single = 0;
        container  buffer(target);
        container  process(target.size());
        container  remain_any(process.size());
        *process.begin() = 1;

        while (operation::less(process, buffer)) {
            operation::multiply_single(process, radix, process, 2);
            operation::quotient_single(buffer, remain_single, radix, buffer, 2);
        }

        do {
            std::copy(process.begin(), process.end(), buffer.begin());
            operation::quotient_any(process, remain_any, radix, target, process);
            operation::plus(process, radix, process, process);
            operation::quotient_single(process, remain_single, radix, process, 2);
        } while (operation::less(process, buffer));
        just = operation::equals(process, buffer);

        src.swap(operation::cut_front_zero(buffer));
        return just;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : change radix value of container                */
    /*------------------------------------------------------------*/
    static container& change(
        container&          src
      , const container&    target
      , const value_type&   base
      , const value_type&   change)
    {
        if (range::invalidity(change) || range::invalidity(base))
            exception::throws(exception::rash_radix_value);

        if (change == base || !target.size()) {
            src.assign(target.begin(), target.end());
            return src;
        }

        digit_type  digits;
        container   buffer;
        container   process;
        container   cardinal;
        container   progress(1, 1);
        const_iterator iTe = target.end();
        const_iterator iTb = target.begin();

        operation::complement(cardinal, change, base);
        selves::check_over_digit(cardinal.size(),
                    selves::check_over_digit(
                        target.size(), cardinal.size(), false));

        for (;iTb != iTe; ++iTb) {
            selves::multiply(process, change, progress, container(1, *iTb));
            digits = std::max(buffer.size(), process.size());
            selves::plus(buffer, change
              , selves::fill_front_zero(buffer,  digits)
              , selves::fill_front_zero(process, digits));
            selves::multiply(progress, change, progress, cardinal);
        }
        src.swap(buffer);
        return src;
    }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_CALCULATOR_HPP__INCLUDED
