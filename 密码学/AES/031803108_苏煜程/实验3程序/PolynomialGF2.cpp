#include <atlstr.h>
#include "PolynomialGF2.h"


PolynomialGF2::PolynomialGF2()
{
}


PolynomialGF2::~PolynomialGF2()
{
}

PolynomialGF2::PolynomialGF2(const INT64 & int64Number)
{
    Number2Polynomial(int64Number, m_deqPolynomial);
} //! Polynomial::Polynomial() END;

PolynomialGF2::PolynomialGF2(const std::initializer_list<BYTE>& kref_initList)
    : PolynomialGF2(std::deque<BYTE>(kref_initList))
{
}

PolynomialGF2::PolynomialGF2(const std::deque<BYTE> &kref_deque)
{
    m_deqPolynomial = kref_deque;
    ClearInvalidZero();
} //! Polynomial::Polynomial() END

PolynomialGF2::PolynomialGF2(const std::vector<BYTE>& kref_vector)
{
    for (const auto element : kref_vector)
    {
        m_deqPolynomial.push_back(element);
    }
    ClearInvalidZero();
} //! PolynomialGF2::PolynomialGF2() END

PolynomialGF2::PolynomialGF2(const PolynomialGF2 &kref_polyRight)
{
    *this = kref_polyRight;
    ClearInvalidZero();
} //! Polynomial::Polynomial() END

PolynomialGF2::PolynomialGF2(PolynomialGF2 &&rvalue_polyRight)
{
    *this = std::move(rvalue_polyRight);
} //! Polynomial::Polynomial() END

PolynomialGF2::PolynomialGF2(const size_t &kuiNumber, const BYTE &kref_cValue)
    : m_deqPolynomial(kuiNumber, kref_cValue)
{
} //! Polynomial::Polynomial() END

PolynomialGF2 &PolynomialGF2::operator=(const PolynomialGF2 &kref_polyRight)
{
    m_deqPolynomial = kref_polyRight.m_deqPolynomial;
    return *this;
} //! Polynomial::operator=() END

PolynomialGF2 &PolynomialGF2::operator=(PolynomialGF2 &&rvalue_polyRight)
{
    m_deqPolynomial = std::move(rvalue_polyRight.m_deqPolynomial);
    return *this;
} //! Polynomial::operator=() END

PolynomialGF2 PolynomialGF2::operator+(const PolynomialGF2 &ref_polyRight)
{
    PolynomialGF2 polyResult = *this;
    int iRightHeighestBitIndex = ref_polyRight.GetHightestBitIndex();
    int iLeftHeighestBitIext = polyResult.GetHightestBitIndex();
    if (iRightHeighestBitIndex > iLeftHeighestBitIext)
    {
        int iGap = iRightHeighestBitIndex - iLeftHeighestBitIext;
        polyResult.Insert(iLeftHeighestBitIext + 1, iGap, 0);
    }

    for (size_t cntI = 0; cntI < (size_t)(iRightHeighestBitIndex + 1); cntI++)
    {
        polyResult[cntI] ^= ref_polyRight[cntI];
    }
    return polyResult;
} //! Polynomial::operator+() END

PolynomialGF2 PolynomialGF2::operator-(const PolynomialGF2 &ref_polyRight)
{
    PolynomialGF2 polyResult = *this;
    int iRightHeighestBitIndex = ref_polyRight.GetHightestBitIndex();
    int iLeftHeighestBitIext = polyResult.GetHightestBitIndex();
    if (iRightHeighestBitIndex > iLeftHeighestBitIext)
    {
        int iGap = iRightHeighestBitIndex - iLeftHeighestBitIext;
        polyResult.Insert(iLeftHeighestBitIext + 1, iGap, 0);
    }

    for (size_t cntI = 0; cntI < ref_polyRight.GetSize(); cntI++)
    {
        polyResult[cntI] ^= ref_polyRight[cntI];
    }
    return polyResult;
} //! Polynomial::operator-() END

PolynomialGF2 PolynomialGF2::operator-(const PolynomialGF2 &ref_polyRight) const
{
    PolynomialGF2 polyResult = *this;
    int iRightHeighestBitIndex = ref_polyRight.GetHightestBitIndex();
    int iLeftHeighestBitIext = polyResult.GetHightestBitIndex();
    if (iRightHeighestBitIndex > iLeftHeighestBitIext)
    {
        int iGap = iRightHeighestBitIndex - iLeftHeighestBitIext;
        polyResult.Insert(iLeftHeighestBitIext + 1, iGap, 0);
    }

    for (size_t cntI = 0; cntI < ref_polyRight.GetSize(); cntI++)
    {
        polyResult[cntI] ^= ref_polyRight[cntI];
    }
    return polyResult;
} //! PolynomialGF2::operator-() END

PolynomialGF2 PolynomialGF2::operator*(const PolynomialGF2 &ref_polyRight)
{
    PolynomialGF2 polyResult;
    for (size_t cntI = 0; cntI < ref_polyRight.GetSize(); cntI++)
    {
        PolynomialGF2 polyTmp = *this;
        if (1 == ref_polyRight[cntI])
        {
            polyTmp.Insert(0, cntI, 0);
            polyResult = polyResult + polyTmp;
        }
    }
    return polyResult;
} //! Polynomial::operator*() END

PolynomialGF2 PolynomialGF2::operator/(const PolynomialGF2 &kref_right)
{
    return *this;
} //! Polynomial::operator/() END

PolynomialGF2 PolynomialGF2::operator%(const PolynomialGF2 &kref_polyRight)
{
    PolynomialGF2 polyResult;
    int iLeftHightestBitIndex = GetHightestBitIndex();
    int iRightHightestBitIndex = kref_polyRight.GetHightestBitIndex();

    if (iLeftHightestBitIndex == iRightHightestBitIndex)
    {
        polyResult = kref_polyRight - *this;
    }
    else if (iLeftHightestBitIndex < iRightHightestBitIndex)
    {
        polyResult = *this;
    }
    else if (iLeftHightestBitIndex > iRightHightestBitIndex)
    {
        PolynomialGF2 polyQuotient;
        Division(kref_polyRight, polyQuotient, polyResult);
    }

    return polyResult;
} //! PolynomialGF2::operator%() END

PolynomialGF2 &PolynomialGF2::operator<<=(const size_t &kref_uiNumber)
{
    m_deqPolynomial.insert(m_deqPolynomial.cbegin(), kref_uiNumber, 0);
    if (m_bEnableLeftMoveLimit &&
        GetHightestBitIndex() >= (int)m_uiLeftMoveLimitBit)
    {
        m_deqPolynomial.erase(std::next(m_deqPolynomial.cbegin(),
                                        m_uiLeftMoveLimitBit),
                              m_deqPolynomial.cend());
    }
    return *this;
} //! PolynomialGF2::operator<<=() END;

PolynomialGF2 &PolynomialGF2::operator^=(const PolynomialGF2 &kref_polyRight)
{
    size_t uiheighBit = 0;
    size_t uiLeftSize = m_deqPolynomial.size();
    size_t uiRightSize = kref_polyRight.GetSize();

    size_t uiOperationSize = uiLeftSize;
    if (uiLeftSize > uiRightSize)
    {
        uiOperationSize = uiRightSize;
    }

    for (size_t cntI = 0; cntI < uiOperationSize; cntI++)
    {
        m_deqPolynomial[cntI] ^= kref_polyRight[cntI];
    }
    return *this;
} //! PolynomialGF2::operator^=() END

std::deque<BYTE>::reference PolynomialGF2::operator[](const size_t uiIndex)
{
    return m_deqPolynomial[uiIndex];
} //! Polynomial::operator[]() END

std::deque<BYTE>::const_reference
PolynomialGF2::operator[](const size_t uiIndex) const
{
    return m_deqPolynomial[uiIndex];
} //! Polynomial::operator[]() END


BOOL PolynomialGF2::Insert(size_t uiPos, size_t uiNumber, BYTE cValue)
{
    auto itorPos = std::next(m_deqPolynomial.cbegin(), uiPos);
    m_deqPolynomial.insert(itorPos, uiNumber, cValue);
    return TRUE;
} //! Polynomial::Insert() END

size_t PolynomialGF2::GetSize() const
{
    return m_deqPolynomial.size();
}

void PolynomialGF2::Clear()
{
    m_deqPolynomial.clear();
} //! Polynomial::Clear() END


BOOL PolynomialGF2::ClearInvalidZero(const size_t &kref_uiPos)
{
    return ClearPolynomialInvalidZero(m_deqPolynomial, kref_uiPos);
} //! PolynomialGF2::ClearInvalidZero() END


BOOL PolynomialGF2::ClearPolynomialInvalidZero(
    std::deque<BYTE> &ref_deqPolynomial,
    const size_t &kref_uiPos
)
{
    BOOL bResult = FALSE;
    do
    {
        if (ref_deqPolynomial.empty())
        {
            break;
        }

        int iHighestBitIndex = GetPolynomialHightestBitIndex(ref_deqPolynomial);
        if (iHighestBitIndex < 0)
        {
            break;
        }

        auto itorkI = std::next(ref_deqPolynomial.cbegin(),
                                iHighestBitIndex + 1);
        ref_deqPolynomial.erase(itorkI, ref_deqPolynomial.cend());

        bResult = TRUE;
    } while (FALSE);

    return bResult;
} //! Polynomial::ClearInvalidZero() END

BOOL PolynomialGF2::Division(const PolynomialGF2 &kref_polyDivisor,
                             PolynomialGF2 &polyQuotient,
                             PolynomialGF2 &polyRemainder)
{
    BOOL bResult = FALSE;
    polyQuotient.Clear();
    polyRemainder.Clear();

    do
    {
        // 找到被除数和除数的最高有效位的指数
        int iFirstDivisorHighestBitIndex = GetHightestBitIndex();
        if (iFirstDivisorHighestBitIndex < 0)
        {
            break;
        }
        int iSecondDivisorHighestBitIndex =
            kref_polyDivisor.GetHightestBitIndex();
        if (iSecondDivisorHighestBitIndex < 0)
        {
            break;
        }

        polyQuotient.Insert(0, iFirstDivisorHighestBitIndex + 1, 0);

        if (iFirstDivisorHighestBitIndex < iSecondDivisorHighestBitIndex)
        {
            break;
        }

        PolynomialGF2 polyTmpRemainder = *this;
        PolynomialGF2 polyTmpSecondDivisor = kref_polyDivisor;
        while (iFirstDivisorHighestBitIndex >= iSecondDivisorHighestBitIndex)
        {
            // 算出指数，然后除数补位
            int iGap =
                iFirstDivisorHighestBitIndex - iSecondDivisorHighestBitIndex;

            polyQuotient[iGap] = 1;
            if (iGap > 0)
            {
                polyTmpSecondDivisor.Insert(0, (size_t)iGap, 0);
            }

            // 计算结果
            for (size_t cntI = 0;
                 cntI <= (size_t)iFirstDivisorHighestBitIndex;
                 cntI++)
            {
                // 在GF(2)上的算术运算
                polyTmpRemainder[cntI] ^= polyTmpSecondDivisor[cntI];
            }

            polyTmpSecondDivisor = kref_polyDivisor;
            iFirstDivisorHighestBitIndex =
                polyTmpRemainder.GetHightestBitIndex();
        }

        polyRemainder = std::move(polyTmpRemainder);

        bResult = true;
    } while (FALSE);

    polyQuotient.ClearInvalidZero();
    polyRemainder.ClearInvalidZero();
    return bResult;
} //! Polynomial::Division() END

INT64 PolynomialGF2::ToNumber()
{
    INT64 i64Number = 0;
    Polynomial2Number(m_deqPolynomial, i64Number);
    return i64Number;
} //! Polynomial::ToNumber() END;

void PolynomialGF2::EnableLeftMoveLimit(const BOOL &kref_bEnable)
{
    m_bEnableLeftMoveLimit = kref_bEnable;
} //! PolynomialGF2::EnableLeftMoveLimit() END

void PolynomialGF2::SetLeftMoveListBit(const size_t &kref_uiBitIndex)
{
    m_uiLeftMoveLimitBit = kref_uiBitIndex;
} //! PolynomialGF2::SetLeftMoveListBit() END

void PolynomialGF2::Number2Polynomial(const INT64 &kref_i64Number,
                                      std::deque<BYTE> &ref_deqPolynomial)
{
    INT64 i64TmpNumber = kref_i64Number;
    BYTE bytBit = 0;
    while (i64TmpNumber > 0)
    {
        bytBit = (BYTE)(i64TmpNumber % 2);
        i64TmpNumber /= 2;
        ref_deqPolynomial.push_back(bytBit);
    }
} //! Polynomial::Number2Polynomial() END

BOOL PolynomialGF2::Polynomial2Number(
    const std::deque<BYTE> &kref_deqPolynomial,
    INT64 &ref_i64Number
)
{
    BOOL bResult = FALSE;
    do
    {
        for (size_t cntI = 0; cntI < kref_deqPolynomial.size(); cntI++)
        {
            if (0 == kref_deqPolynomial[cntI])
            {
                continue;
            }
            ref_i64Number += (INT64)pow(2, cntI);
        }

        bResult = TRUE;
    } while (FALSE);

    return bResult;
} //! Polynomial::Polynomial2Number() END


void PolynomialGF2::PaddingZero(const size_t &kref_uiPosition)
{
    if (m_deqPolynomial.size() < kref_uiPosition)
    {
        size_t uiPaddingNumber = kref_uiPosition - m_deqPolynomial.size();
        m_deqPolynomial.insert(m_deqPolynomial.cend(), uiPaddingNumber, 0);;;;
    }
}

BOOL PolynomialGF2::EqualZero() const
{
    BOOL bReuslt = TRUE;

    for (const auto element : m_deqPolynomial)
    {
        if (0 != element)
        {
            bReuslt = FALSE;
            break;
        }
    }
    return bReuslt;
} //! Polynomial::EqualZeor() END

std::string PolynomialGF2::GetWrittenFormat() const
{
    return getPolynomialWrittenFormat(m_deqPolynomial);
} //! Polynomial::getFormulaFormat() END

std::string PolynomialGF2::getPolynomialWrittenFormat(
    const std::deque<BYTE> &deqPolynomial
)
{
    std::string strWrittenFormat;
    CStringA csIndex;

    for (auto itorI = deqPolynomial.crbegin();
         deqPolynomial.crend() != itorI;
         itorI++)
    {
        if (0 == *itorI)
        {
            continue;
        }
        int iIndex = std::distance(itorI, deqPolynomial.rend());
        iIndex -= 1;

        std::string strValue = "1";
        if (iIndex != 0)
        {
            strValue = "x";
            if (iIndex > 1)
            {
                csIndex.Format("%d", iIndex);
                strValue = "x^";
                strValue += csIndex;
            }
        }

        if (!strWrittenFormat.empty())
        {
            strWrittenFormat += " + ";
        }
        strWrittenFormat += strValue;
    }

    return strWrittenFormat.empty() ? "0" : strWrittenFormat;
} //! Polynomial::getPolynomialWrittenFormat() END

int PolynomialGF2::GetHightestBitIndex() const
{
    return GetPolynomialHightestBitIndex(m_deqPolynomial);
} //! Polynomial::GetHightestBitIndex() END

int PolynomialGF2::GetPolynomialHightestBitIndex(const std::deque<BYTE>& deqPolynomial)
{
    int iIndex = -1;

    auto itorElement =
        std::find(deqPolynomial.rbegin(), deqPolynomial.rend(), 1);
    if (deqPolynomial.rend() != itorElement)
    {
        iIndex = std::distance(itorElement, deqPolynomial.rend());
        iIndex -= 1;
    }

    return iIndex;
} //! Polynomial::GetPolynomialHightestBitIndex() END
