#ifndef POLYNOMIALGF2_H_
#define POLYNOMIALGF2_H_
#include <Windows.h>
#include <deque>
#include <string>
#include <vector>

class PolynomialGF2
{
public:
    PolynomialGF2();
    virtual ~PolynomialGF2();

    PolynomialGF2(const INT64 &int64Number);
    PolynomialGF2(const std::initializer_list<BYTE> &kref_initList);
    PolynomialGF2(const std::deque<BYTE> &kref_deque);
    PolynomialGF2(const std::vector<BYTE> &kref_vector);
    PolynomialGF2(const PolynomialGF2 &kref_polyRight);
    PolynomialGF2(PolynomialGF2 &&rvalue_polyRight);
    PolynomialGF2(const size_t &kuiNumber, const BYTE &kValue);

    PolynomialGF2 &operator=(const PolynomialGF2 &kref_polyRight);
    PolynomialGF2 &operator=(PolynomialGF2 &&rvalue_polyRight);
    PolynomialGF2 operator+(const PolynomialGF2 &kref_polyRight);
    PolynomialGF2 operator-(const PolynomialGF2 &kref_polyRight);
    PolynomialGF2 operator-(const PolynomialGF2 &kref_polyRight) const;
    PolynomialGF2 operator*(const PolynomialGF2 &kref_polyRight);
    PolynomialGF2 operator/(const PolynomialGF2 &kref_polyRight);
    PolynomialGF2 operator%(const PolynomialGF2 &kref_polyRight);

    PolynomialGF2 &operator<<=(const size_t &kref_uiNumber);
    PolynomialGF2 &operator^=(const PolynomialGF2 &kref_poly);
    std::deque<BYTE>::reference operator[](const size_t uiIndex);
    std::deque<BYTE>::const_reference operator[](const size_t uiIndex) const;

    BOOL Insert(size_t uiPos, size_t uiNumber, BYTE cValue);
    size_t GetSize() const;

    void Clear();
    BOOL ClearInvalidZero(const size_t &kref_uiPos = 0);
    static BOOL ClearPolynomialInvalidZero(std::deque<BYTE> &deqPolynomial,
                                           const size_t &kerf_uiPos = 0);

    BOOL Division(const PolynomialGF2 &kref_Polynomial,
                  PolynomialGF2 &Quotient,
                  PolynomialGF2 &Remainder);

    INT64 ToNumber();

    void EnableLeftMoveLimit(const BOOL &kref_bEnable = TRUE);
    void SetLeftMoveListBit(const size_t &kref_uiBitIndex);
    static void Number2Polynomial(const INT64 &kref_i64Number,
                                  std::deque<BYTE> &ref_deqPolynomial);
    static BOOL Polynomial2Number(const std::deque<BYTE> &kref_deqPolynomial,
                                  INT64 &ref_i64Number);

    std::deque<BYTE> GetDequeFormat() const
    {
        return m_deqPolynomial;
    }

    void PaddingZero(const size_t & kref_uiPosition);

    BOOL EqualZero() const;

    std::string GetWrittenFormat() const;
    static std::string getPolynomialWrittenFormat(
        const std::deque<BYTE> &deqPolynomial
    );

    int GetHightestBitIndex() const;
    static int GetPolynomialHightestBitIndex(
        const std::deque<BYTE> &deqPolynomial
    );

    static BOOL CheckPolynomialFormat(const std::deque<BYTE> &deqPolynomial);
private:
    BOOL CheckFormat();
private:
    // 位置表示指数，从首到尾依次升高
    std::deque<BYTE> m_deqPolynomial;
    BOOL m_bEnableLeftMoveLimit = FALSE;
    size_t m_uiLeftMoveLimitBit = 0;
};

#endif // !POLYNOMIALGF2_H_
