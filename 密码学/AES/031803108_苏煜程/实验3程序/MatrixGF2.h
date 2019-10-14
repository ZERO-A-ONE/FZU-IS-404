#ifndef MATRIXGF2_H_
#define MATRIXGF2_H_
#include <vector>
#include <atlstr.h>
#include "PolynomialGF2.h"

template<typename T>
class MatrixGF2
{
private:
    std::vector<std::vector<T>> m_vctMatrix;
    BOOL m_bMultiplicationLimit = FALSE;
    PolynomialGF2 m_polyLimit;
public:
    MatrixGF2();
    ~MatrixGF2();

    MatrixGF2(const INT64 &kref_i64Number);
    MatrixGF2(const MatrixGF2 &rvlaue_mtxRight);
    MatrixGF2(MatrixGF2 &&rvlaue_mtxRight);
    MatrixGF2(const std::initializer_list<std::vector<T>> &kref_initList);
    MatrixGF2(const std::initializer_list<T> &kref_initList);
    MatrixGF2(const std::deque<T> &kref_deqRight);
    MatrixGF2(const size_t &kref_uiRow,
              const size_t &kref_uiColumn,
              const T kref_value);

    MatrixGF2<T> operator+(const MatrixGF2<T> &kref_mtxRight);
    MatrixGF2<T> operator*(const MatrixGF2<T> &kref_mtxRight);
    MatrixGF2<T> &operator=(const MatrixGF2<T> &kref_maxRight);
    MatrixGF2<T> &operator=(MatrixGF2<T> &&rvalue_mtxRight);
    bool operator==(const MatrixGF2<T> &rvalue_mtxRight);
    auto operator[](const size_t kuiIndex) -> decltype(m_vctMatrix[0])
    {
        return m_vctMatrix[kuiIndex];
    }

    void PaddingRow(const size_t &uiTarget);

    void Clear();
    void InsertRow(const size_t &kref_uiPos,
                   const size_t &kref_uiNumber,
                   const size_t &kref_uiSize,
                   const T &kref_value);
    void InsertColumn(const size_t &kref_uiPos,
                      const size_t &kuiNumber,
                      const T &kref_value);
    void Init(const size_t &kref_uiRow,
              const size_t &kref_uiColumn,
              const T &kref_value);

    void SetModleNumberLimit(const PolynomialGF2 &kref_polyModle);
    void EnableMultiplicationLimit(const BOOL &kref_bEnable = TRUE)
    {

    }
    auto operator[](const size_t kuiIndex) const;
    size_t GetRowNumber() const;
    size_t GetColumnNumber() const;

    std::string GetWrittenFormat() const;
    std::vector<T> Transform2Vector() const;
};

template<typename T>
MatrixGF2<T>::MatrixGF2()
{
}


template<typename T>
MatrixGF2<T>::~MatrixGF2()
{
}

template<typename T>
inline MatrixGF2<T>::MatrixGF2(const INT64 &kref_i64Number)
{
    INT64 i64TmpNumber = kref_i64Number;
    BYTE bytBit = 0;
    while (i64TmpNumber > 0)
    {
        bytBit = (BYTE)(i64TmpNumber % 2);
        i64TmpNumber /= 2;
        m_vctMatrix.push_back(std::vector<T>{ bytBit });
    }
} //! MatrixGF2<T>::MatrixGF2() END

template<typename T>
inline MatrixGF2<T>::MatrixGF2(const MatrixGF2 &rvlaue_mtxRight)
{
    m_vctMatrix = rvlaue_mtxRight.m_vctMatrix;
} //! MatrixGF2<T>::MatrixGF2() END

template<typename T>
inline MatrixGF2<T>::MatrixGF2(MatrixGF2 &&rvlaue_mtxRight)
{
    m_vctMatrix = std::move(rvlaue_mtxRight.m_vctMatrix);
} //! MatrixGF2<T>::MatrixGF2() END

template<typename T>
MatrixGF2<T>::MatrixGF2(
    const std::initializer_list<std::vector<T>> &kref_initList
)
{
    m_vctMatrix = kref_initList;
} //! MatrixGF2<T>::MatrixGF2() END

template<typename T>
MatrixGF2<T>::MatrixGF2(const std::initializer_list<T> &kref_initList
)
{
    for (const auto element : kref_initList)
    {
        m_vctMatrix.push_back(std::vector<T>{element});
    }
} //! MatrixGF2<T>::MatrixGF2() END

template<typename T>
inline MatrixGF2<T>::MatrixGF2(const std::deque<T>& kref_deqRight)
{
    for (const auto element : kref_deqRight)
    {
        m_vctMatrix.push_back(std::vector<T>{element});
    }
} //! MatrixGF2<T>::MatrixGF2() END

template<typename T>
MatrixGF2<T>::MatrixGF2(const size_t &uiRow,
                        const size_t &uiColumn,
                        const T value)
    : m_vctMatrix(uiRow, std::vector<T>(uiColumn, value))
{
} //! MatrixGF2<T>::MatrixGF2() END

template<typename T>
inline MatrixGF2<T> MatrixGF2<T>::operator+(const MatrixGF2<T>& kref_mtxRight)
{
    size_t uiLeftColumnNumber = GetColumnNumber();
    size_t uiLeftRowNumber = GetRowNumber();
    size_t uiRightRowNumber = kref_mtxRight.GetRowNumber();
    size_t uiRightColumnNumber = kref_mtxRight.GetColumnNumber();

    if (uiLeftColumnNumber != uiRightColumnNumber
        || uiLeftRowNumber != uiLeftRowNumber)
    {
        throw std::runtime_error("column number or row number isn't equal");
    }

    MatrixGF2<T> mtxResult = *this;

    for (size_t cntI = 0; cntI < uiLeftRowNumber; cntI++)
    {
        for (size_t cntJ = 0; cntJ < uiLeftColumnNumber; cntJ++)
        {
            mtxResult[cntI][cntJ] ^= kref_mtxRight[cntI][cntJ];
        }
    }
    return mtxResult;
} //! MatrixGF2<T>::operator+() END

template<typename T>
MatrixGF2<T> MatrixGF2<T>::operator*(const MatrixGF2<T> &kref_mtxRight)
{
    size_t uiLeftColumnNumber = GetColumnNumber();
    size_t uiLeftRowNumber = GetRowNumber();
    size_t uiRightRowNumber = kref_mtxRight.GetRowNumber();
    size_t uiRightColumnNumber = kref_mtxRight.GetColumnNumber();
    if (uiLeftColumnNumber != uiRightRowNumber)
    {
        throw std::runtime_error("left column number isn't "
                                 "equal right row number!");
    }

    size_t uiResultRowNumber = uiRightRowNumber;
    size_t uiResultColumnNumber =
        uiRightColumnNumber < uiLeftColumnNumber ?
        uiRightColumnNumber : uiLeftColumnNumber;

    MatrixGF2<T> mtxResult(uiResultRowNumber, uiRightColumnNumber, 0);

    PolynomialGF2 polyTmp;
    polyTmp.EnableLeftMoveLimit();
    size_t uiHeighBit = m_polyLimit.GetHightestBitIndex();
    polyTmp.SetLeftMoveListBit(uiHeighBit);
    for (size_t cntI = 0; cntI < (size_t)uiRightColumnNumber; cntI++)
    {
        for (size_t cntJ = 0; cntJ < (size_t)uiRightRowNumber; cntJ++)
        {
            for (size_t cntK = 0; cntK < (size_t)uiLeftColumnNumber; cntK++)
            {
                if (!m_bMultiplicationLimit)
                {
                    mtxResult[cntJ][cntI] ^=
                        m_vctMatrix[cntJ][cntK] * kref_mtxRight[cntK][cntI];
                }
                else
                {
                    T bigValue = m_vctMatrix[cntJ][cntK];
                    T smallValue = kref_mtxRight[cntK][cntI];
                    if (kref_mtxRight[cntK][cntI] > m_vctMatrix[cntJ][cntK])
                    {
                        bigValue = kref_mtxRight[cntK][cntI];
                        smallValue = m_vctMatrix[cntJ][cntK];
                    }

                    size_t uiLeftMoveNumber = smallValue / 2;
                    size_t uiSelf = smallValue % 2;
                    polyTmp = bigValue;
                    while (uiLeftMoveNumber > 0)
                    {
                        if (polyTmp.GetHightestBitIndex() == (uiHeighBit - 1))
                        {
                            polyTmp <<= 1;
                            polyTmp ^= m_polyLimit;
                        }
                        else
                        {
                            polyTmp <<= 1;
                        }
                        uiLeftMoveNumber--;
                    }

                    if (0 != uiSelf && 0 != uiLeftMoveNumber)
                    {
                        mtxResult[cntJ][cntI] ^=
                            (BYTE)polyTmp.ToNumber() ^ bigValue;
                    }
                    else
                    {
                        mtxResult[cntJ][cntI] ^= (BYTE)polyTmp.ToNumber();
                    }
                }
            }
        }
    }

    return mtxResult;
} //! MatrixGF2<T>::operator*() END

template<typename T>
MatrixGF2<T> &MatrixGF2<T>::operator=(const MatrixGF2<T> &ref_mtxRight)
{
    m_vctMatrix = ref_mtxRight.m_vctMatrix;
    return *this;
} //! MatrixGF2<T>::operator=() END

template<typename T>
MatrixGF2<T> &MatrixGF2<T>::operator=(MatrixGF2<T> &&rvalue_mtxRight)
{
    m_vctMatrix = std::move(rvalue_mtxRight.m_vctMatrix);
    return *this;
} //! MatrixGF2<T>::operator=() END

template<typename T>
inline bool MatrixGF2<T>::operator==(const MatrixGF2<T> &rvalue_mtxRight)
{
    BOOL bResult = TRUE;

    do
    {
        size_t uiColumnNumber = GetColumnNumber();
        size_t uiRowNumber = GetRowNumber();
        if (uiColumnNumber != rvalue_mtxRight.GetColumnNumber() ||
            uiRowNumber != rvalue_mtxRight.GetRowNumber())
        {
            break;
        }

        BOOL bEqual = TRUE;
        for (size_t cntI = 0; cntI < uiColumnNumber; cntI++)
        {
            for (size_t cntJ = 0; cntJ < uiRowNumber; cntJ++)
            {
                if (m_vctMatrix[cntI][cntJ] != rvalue_mtxRight[cntI][cntJ])
                {
                    bResult = FALSE;
                    break;
                }
            }

            if (!bResult)
            {
                break;
            }
        }
    } while (FALSE);
    return bResult;
}

template<typename T>
inline void MatrixGF2<T>::PaddingRow(const size_t &kref_uiTarget)
{
    size_t uiRowNumber = GetRowNumber();
    if (uiRowNumber >= kref_uiTarget)
    {
        return;
    }

    InsertRow(uiRowNumber, kref_uiTarget - uiRowNumber, GetColumnNumber(), 0);
} //! MatrixGF2<T>::PaddingRow() END

template<typename T>
inline void MatrixGF2<T>::Clear()
{
    m_vctMatrix.clear();
} //! MatrixGF2<T>::Clear() END

template<typename T>
inline void MatrixGF2<T>::InsertRow(const size_t &kref_uiPos,
                                    const size_t &kref_uiNumber,
                                    const size_t &kref_uiSize,
                                    const T &kref_value)
{
    auto itorPos = std::next(m_vctMatrix.cbegin(), kref_uiPos);
    m_vctMatrix.insert(itorPos,
                       kref_uiNumber,
                       std::vector<T>(kref_uiSize, kref_value));
} //! MatrixGF2<T>::InsertRow() END

template<typename T>
inline void MatrixGF2<T>::Init(const size_t &kref_uiRow,
                               const size_t &kref_uiColumn,
                               const T &kref_value)
{
    Clear();
    InsertRow(0, kref_uiRow, kref_uiColumn, kref_value);
} //! MatrixGF2<T>::Init() END

template<typename T>
inline void MatrixGF2<T>::SetModleNumberLimit(
    const PolynomialGF2 &kref_polyModle
)
{
    m_polyLimit = kref_polyModle;
} //! MatrixGF2<T>::SetModleNumberLimit() END

template<typename T>
inline auto MatrixGF2<T>::operator[](const size_t uiIndex) const
{
    return m_vctMatrix[uiIndex];
} //! MatrixGF2<T>::operator[]() END


template<typename T>
inline size_t MatrixGF2<T>::GetRowNumber() const
{
    return m_vctMatrix.size();
} //! MatrixGF2<T>::GetRowNum() END

template<typename T>
inline size_t MatrixGF2<T>::GetColumnNumber() const
{
    if (m_vctMatrix.empty())
    {
        return 0;
    }
    return m_vctMatrix[0].size();
} //! MatrixGF2<T>::GetColumnNum() END

template<typename T>
inline std::string MatrixGF2<T>::GetWrittenFormat() const
{
    std::string strWrittenFormat;
    for (const auto row : m_vctMatrix)
    {
        std::string strRow;
        for (const auto element : row)
        {
            if (!strRow.empty())
            {
                strRow += ", ";
            }
            CStringA csaElement;
            csaElement.Format("0x%02X", element);
            strRow += csaElement.GetString();
        }
        strRow += "\n";
        strWrittenFormat += strRow;
    }

    return strWrittenFormat;
} //! MatrixGF2<T>::getWrittenFormat() END

template<typename T>
inline std::vector<T> MatrixGF2<T>::Transform2Vector() const
{
    if (GetColumnNumber() != 1)
    {
        throw std::runtime_error("Column number is illegal");
    }

    std::vector<T> m_vctFormat;
    size_t uiRowNumber = GetRowNumber();
    for (size_t cntI = 0; cntI < uiRowNumber; cntI++)
    {
        m_vctFormat.push_back(m_vctMatrix[cntI][0]);
    }

    return m_vctFormat;
} //! MatrixGF2<T>::Transform2Vector() END


#endif // !MATRIXGF2_H_
