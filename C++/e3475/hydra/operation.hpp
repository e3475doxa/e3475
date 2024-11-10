/*---------------------------------------------------------------------------*/
/*! @created   : 2005/07/31                                                  */
/*! @update    : 2006/01/29                                                  */
/*! @version   : 2.0.0                                                       */
/*! @filename  : operation.hpp                                               */
/*! @author    : e3475 <linemaster>                                          */
/*! @copyright : All Rights Reserved. Copyright (c) e3475 2005-2006.         */
/*---------------------------------------------------------------------------*/
/*! @details   : hydra template : definition for hydra's operation           */
/*---------------------------------------------------------------------------*/
#ifndef E3475__HYDRA_OPERATION_HPP__INCLUDED
#define E3475__HYDRA_OPERATION_HPP__INCLUDED 200

//-----------------------//
// initialized namespace //
//-----------------------//
namespace e3475 {
namespace details {
namespace hydra {

//---------------------------------------------------------------------------//
// structure : definition for hydra's operation template                     //
//---------------------------------------------------------------------------//
template <typename HydraGlobals>
struct hydra_operation
{
    typedef HydraGlobals                            global;
    typedef hydra_operation<global>                 selves;
    typedef typename global::args                   args;
    typedef typename global::exception              exception;
    typedef typename args::container                container;
    typedef typename args::value_type               value_type;
    typedef typename args::digit_type               digit_type;
    typedef typename args::iterator                 iterator;
    typedef typename args::const_iterator           const_iterator;
    typedef typename args::reverse_iterator         reverse_iterator;
    typedef typename args::const_reverse_iterator   const_reverse_iterator;

    /*------------------------------------------------------------*/
    /*! @brief   : complement transfer value                      */
    /*------------------------------------------------------------*/
    static void complement(
        container&          src
      , const value_type&   radix
      , const value_type&   transfer)
    {
        value_type tmp = transfer;
        do src.push_back(tmp % radix);
        while (tmp /= radix);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : filling front area with zero                   */
    /*------------------------------------------------------------*/
    static container& fill_front_zero(
        container&          src
      , const digit_type&   digit)
    {
        src.insert(src.end(), digit - src.size(), 0);
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : cutting front area with zero                   */
    /*------------------------------------------------------------*/
    static container& cut_front_zero(
        container&      src)
    {
        reverse_iterator tmp
            = std::find_if(src.rbegin(), src.rend(), 
                boost::bind(std::not_equal_to<value_type>(), _1, 0));
        src.erase(tmp.base(), src.end());
        return src;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : comparisons equal A B (A == B)                 */
    /*------------------------------------------------------------*/
    static bool equals(
        const container&    A
      , const container&    B)
    {
        return std::equal(A.begin(), A.end(), B.begin());
    }

    /*------------------------------------------------------------*/
    /*! @brief   : comparisons less A B (A < B)                   */
    /*------------------------------------------------------------*/
    static bool less(
        const container&    A
      , const container&    B
      , const bool&         charm = true)
    {
        const_reverse_iterator iAre = A.rend();
        const_reverse_iterator iArb = A.rbegin();
        const_reverse_iterator iBrb = B.rbegin();
        for (; iArb != iAre; ++iArb,++iBrb) 
            if (*iArb != *iBrb) return (*iArb < *iBrb) ? true : false;
        return charm == false;
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations plus A B (A + B)                    */
    /*------------------------------------------------------------*/
    static void plus(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        value_type      quotients = 0, transfer = 0;
        iterator        iSb = src.begin();
        const_iterator  iAb = A.begin();
        const_iterator  iBb = B.begin();
        const_iterator  iAe = A.end();

        for (; iAb != iAe; ++iAb, ++iBb, ++iSb) {
            quotients = *iAb + *iBb + transfer;
            if (quotients >= radix) {
                transfer  = quotients / radix;
                quotients = quotients % radix;
            } else transfer = 0;
            *iSb = quotients;
        }
        if (transfer) {
            *iSb = transfer % radix;
            if (transfer /= radix)
                selves::complement(src, radix, transfer);
        }
    }

    /*------------------------------------------------------------*/
    /*! @brief   : operations minus A B (A - B)                   */
    /*------------------------------------------------------------*/
    static void minus(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        value_type      quotients = 0, debt = 0;
        iterator        iSb = src.begin();
        const_iterator  iAb = A.begin();
        const_iterator  iBb = B.begin();
        const_iterator  iAe = A.end();

        for (; iAb != iAe; ++iAb, ++iBb, ++iSb) {
            if (*iAb >= (*iBb + debt)) {
                quotients = *iAb - (*iBb + debt);
                debt      = 0;
            } else {
                quotients = (radix + *iAb) - (*iBb + debt);
                debt      = 1;
            }
            *iSb = quotients;
        }
        if (debt) exception::throws(exception::calc_contradict);
    }

    /*------------------------------------------------------------*/
    /*! @brief   : single digit operations multiply A B (A * B)   */
    /*------------------------------------------------------------*/
    static void multiply_single(
        container&          src
      , const value_type&   radix
      , const container&    A
      , const value_type&   B)
    {
        const_iterator iAe = A.end();
        const_iterator iAb = A.begin();
        iterator       iSb = src.begin();
        value_type     quotients = 0, transfer = 0;

        for (; iAb != iAe; ++iAb, ++iSb) {
            quotients = (*iAb * B) + transfer;
            if (quotients >= radix) {
                transfer  = quotients / radix;
                quotients = quotients % radix;
            } else transfer = 0;
            *iSb = quotients;
        }
        if (transfer) {
            *iSb = transfer % radix;
            if (transfer /= radix)
                selves::complement(src, radix, transfer);
        }
    }

    /*------------------------------------------------------------*/
    /*! @brief   : any digits operations multiply A B (A * B)     */
    /*------------------------------------------------------------*/
    static void multiply_any(
        container&          src
      , container&          process
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        const_iterator  iBb = B.begin();
        const_iterator  iBe = B.end();
        const_iterator  iAe = A.end();
        value_type      quotients = 0, transfer = 0;
        digit_type      digits  = 0;

        for (; iBb != iBe; ++iBb, ++digits, transfer = 0) {
            std::fill(process.begin(), process.end(), 0);
            const_iterator iAb = A.begin();
            iterator       iPb = process.begin() + digits;
            for (; iAb != iAe; ++iAb, ++iPb) {
                quotients = (*iAb * *iBb) + transfer;
                if (quotients >= radix) {
                    transfer  = quotients / radix;
                    quotients = quotients % radix;
                } else transfer = 0;
                *iPb = quotients;
            }
            if (transfer) {
                *iPb = transfer % radix;
                if (transfer /= radix)
                    selves::complement(src, radix, transfer);
            }
            selves::plus(src, radix, src, process);
        }
    }

    /*------------------------------------------------------------*/
    /*! @brief   : single digit operations quotient A B (A / B)   */
    /*------------------------------------------------------------*/
    static void quotient_single(
        container&          quotnt
      , value_type&         remain
      , const value_type&   radix
      , const container&    A
      , const value_type&   B)
    {
        reverse_iterator       iQb  = quotnt.rbegin();
        const_reverse_iterator iArb = A.rbegin();
        const_reverse_iterator iAre = A.rend();

        for (; iArb != iAre; ++iArb, ++iQb) {
            remain = *iArb + radix * remain;
            *iQb   = remain / B;
            remain = remain % B;
        }
    }

    /*------------------------------------------------------------*/
    /*! @brief   : any digits operations quotient A B (A / B)     */
    /*------------------------------------------------------------*/
    static void quotient_any(
        container&          quotnt
      , container&          remain
      , const value_type&   radix
      , const container&    A
      , const container&    B)
    {
        reverse_iterator       iQb  = quotnt.rbegin();
        const_reverse_iterator iArb = A.rbegin();
        const_reverse_iterator iAre = A.rend();
        value_type             operand = 0;

        for (; iArb != iAre; ++iArb, ++iQb, operand = 0) {
            std::copy(++remain.rbegin(), remain.rend(), remain.rbegin());
            *remain.begin() = *iArb;
            for (; !selves::less(remain, B); ++operand)
                selves::minus(remain, radix, remain, B);
            *iQb = operand;
        }
    }
};

//---------------------//
// finalized namespace //
//---------------------//
}}}

#endif // !E3475__HYDRA_OPERATION_HPP__INCLUDED
