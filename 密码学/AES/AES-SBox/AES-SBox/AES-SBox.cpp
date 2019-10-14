#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "MatrixGF2.h"
#include "PolynomialGF2.h"

MatrixGF2<BYTE> g_mtxPositiveBox(16, 16, 0);
MatrixGF2<BYTE> g_mtxReverseBox(16, 16, 0);
MatrixGF2<BYTE> g_mtxBytePositiveTransformMatrix(8, 8, 0);
MatrixGF2<BYTE> g_mtxByteReverseTransformMatrix(8, 8, 0);
BYTE g_bytPositiveFixed = 0;
BYTE g_bytReverseFixed = 0;
PolynomialGF2 g_polyModle;

#define MAKEBYTE(_high, _low) (((_high) << 4) | (_low))

PolynomialGF2 PolynomialEuclidEx(const PolynomialGF2 &kref_polyA,
                                 const PolynomialGF2 &kref_polyB,
                                 PolynomialGF2 &ref_polyX,
                                 PolynomialGF2 &ref_polyY)
{
    if (kref_polyB.EqualZero())
    {
        throw std::runtime_error("The polyB is zero!");
    }

    int iHighestBitIndex = kref_polyA.GetHightestBitIndex();

    PolynomialGF2 polyQuotient(iHighestBitIndex + 1, 0);
    PolynomialGF2 polyRemainder(iHighestBitIndex + 1, 0);
    PolynomialGF2 polyLastLastX(iHighestBitIndex + 1, 0);
    polyLastLastX = 1;
    PolynomialGF2 polyLastLastY(iHighestBitIndex + 1, 0);
    PolynomialGF2 polyLastLastRemainder = kref_polyA;
    PolynomialGF2 polyLastX(iHighestBitIndex + 1, 0);
    PolynomialGF2 polyLastY(iHighestBitIndex + 1, 0);
    polyLastY = 1;
    PolynomialGF2 polyLastRemainder = kref_polyB;

    ref_polyX.Clear();
    ref_polyY.Clear();
    ref_polyX.Insert(0, iHighestBitIndex + 1, 0);
    ref_polyY.Insert(0, iHighestBitIndex + 1, 0);
    ref_polyY = 1;

    do
    {
        polyLastLastRemainder.Division(polyLastRemainder,
                                       polyQuotient,
                                       polyRemainder);
        if (polyRemainder.EqualZero())
        {
            break;
        }

        ref_polyX = polyLastLastX - polyLastX * polyQuotient;
        ref_polyY = polyLastLastY - polyLastY * polyQuotient;

        polyLastLastRemainder = polyLastRemainder;
        polyLastRemainder = polyRemainder;
        polyLastLastX = polyLastX;
        polyLastLastY = polyLastY;
        polyLastX = ref_polyX;
        polyLastY = ref_polyY;
    } while (TRUE);
    return polyLastRemainder;
} //! PolynomialGF2EuclidEx() END

void InitByteTransformMatrix(PolynomialGF2 &ref_polyInit,
                             MatrixGF2<BYTE> &ref_mtxTarget)
{
    size_t uiColumnNumber = ref_mtxTarget.GetColumnNumber();
    if (ref_polyInit.GetSize() != ref_mtxTarget.GetColumnNumber())
    {
        ref_polyInit.PaddingZero(uiColumnNumber);
    }

    size_t uiRowNumber = uiColumnNumber;
    for (size_t cntY = 0; cntY < uiRowNumber; cntY++)
    {
        size_t iOffset = cntY;
        for (size_t cntX = 0; cntX < uiColumnNumber; cntX++)
        {
            size_t iActualPos = cntX + iOffset;
            if (iActualPos >= uiColumnNumber)
            {
                iActualPos -= uiColumnNumber;
            }
            ref_mtxTarget[cntY][iActualPos] = ref_polyInit[cntX];
        }
    }
} //! InitByteTransformMatrix() END

void InitPositiveBox()
{
    MatrixGF2<BYTE> mtxFixed = PolynomialGF2(g_bytPositiveFixed).GetDequeFormat();

    for (size_t cntY = 0; cntY < 16; cntY++)
    {
        for (size_t cntX = 0; cntX < 16; cntX++)
        {
            BYTE bytSource = (BYTE)MAKEBYTE(cntY, cntX);
            if (0 == bytSource)
            {
                g_mtxPositiveBox[cntY][cntX] = g_bytPositiveFixed;
                continue;
            }

            PolynomialGF2 polyInverseElement;
            PolynomialGF2 polyX;
            PolynomialGF2 polySource = bytSource;

            // 求乘法逆元
            if (!polySource.EqualZero())
            {
                PolynomialGF2 polyResult =
                    PolynomialEuclidEx(g_polyModle,
                                       polySource,
                                       polyX,
                                       polyInverseElement);
            }
            else
            {
                polyInverseElement = { 0 };
            }
            polyInverseElement.ClearInvalidZero();
            MatrixGF2<BYTE> mtxValue = polyInverseElement.GetDequeFormat();

            mtxValue.PaddingRow(
                g_mtxBytePositiveTransformMatrix.GetColumnNumber()
            );
            mtxFixed.PaddingRow(mtxValue.GetRowNumber());

            mtxValue = g_mtxBytePositiveTransformMatrix * mtxValue + mtxFixed;
            g_mtxPositiveBox[cntY][cntX] =
                (BYTE)PolynomialGF2(mtxValue.Transform2Vector()).ToNumber();
        }
    }
} //! InitPositiveBox() END

void InitReverseBox()
{
    MatrixGF2<BYTE> mtxFixed = PolynomialGF2(g_bytReverseFixed).GetDequeFormat();

    for (size_t cntY = 0; cntY < 16; cntY++)
    {
        for (size_t cntX = 0; cntX < 16; cntX++)
        {
            BYTE bytSource = (BYTE)MAKEBYTE(cntY, cntX);
            MatrixGF2<BYTE> mtxValue = bytSource;
            int iValueColumnNumber =
                g_mtxByteReverseTransformMatrix.GetColumnNumber();
            if (0 == bytSource)
            {
                mtxValue.InsertRow(0, iValueColumnNumber, 1, 0);
            }
            mtxValue.PaddingRow(iValueColumnNumber);
            mtxFixed.PaddingRow(mtxValue.GetRowNumber());
            mtxValue = g_mtxByteReverseTransformMatrix * mtxValue + mtxFixed;

            PolynomialGF2 polyInverseElement;
            PolynomialGF2 polyX;
            PolynomialGF2 polyValue = mtxValue.Transform2Vector();

            if (!polyValue.EqualZero())
            {
                // 求乘法逆元
                PolynomialGF2 polyResult =
                    PolynomialEuclidEx(g_polyModle,
                                       polyValue,
                                       polyX,
                                       polyInverseElement);
            }
            else
            {
                polyInverseElement = { 0 };
            }

            g_mtxReverseBox[cntY][cntX] = (BYTE)polyInverseElement.ToNumber();
        }
    }
} //! InitReverseBox() END

void GetReverseTransfarmMatrix()
{
    PolynomialGF2 polyPositiveSeed = { 0, 1, 1, 1, 0, 1, 0, 1 };
    InitByteTransformMatrix(polyPositiveSeed, g_mtxBytePositiveTransformMatrix);

    MatrixGF2<BYTE> mtxResult(8, 8, 0);
    PolynomialGF2 polyReverseSeed = { 1, 0, 0, 0, 0, 0, 0, 0 };
    InitByteTransformMatrix(polyReverseSeed, mtxResult);
    MatrixGF2<BYTE> mtxReverseTransformMatrix;
    size_t uiPositiveColumnNumber = g_mtxBytePositiveTransformMatrix.GetColumnNumber();
    for (size_t cntI = 1; cntI <= 0xFF; cntI++)
    {
        MatrixGF2<BYTE> mtxTmp(8, 8, 0);
        PolynomialGF2 polyTmp = cntI;
        polyTmp.PaddingZero(8);
        InitByteTransformMatrix(polyTmp, mtxTmp);
        if (g_mtxBytePositiveTransformMatrix * mtxTmp == mtxResult)
        {
            printf("B: \n%s\n", mtxTmp.GetWrittenFormat().c_str());
            MatrixGF2<BYTE> mtxPositiveFixed = PolynomialGF2(0x28).GetDequeFormat();
            mtxPositiveFixed.PaddingRow(8);
            MatrixGF2<BYTE> mtxReverseFixed = mtxTmp * mtxPositiveFixed;
            printf("d_i: 0x%2llX",
                   PolynomialGF2(mtxReverseFixed.Transform2Vector()).ToNumber());
        }
    }
} //! GetReverseTransfarmMatrix() END

void InitStandardBox()
{
    g_polyModle = { 1, 1, 0, 1, 1, 0, 0, 0, 1 };
    PolynomialGF2 polyPositiveSeed = { 1, 0, 0, 0, 1, 1, 1, 1 };
    InitByteTransformMatrix(polyPositiveSeed, g_mtxBytePositiveTransformMatrix);
    PolynomialGF2 polyReverseSeed = { 0, 0, 1, 0, 0, 1, 0, 1 };
    InitByteTransformMatrix(polyReverseSeed, g_mtxByteReverseTransformMatrix);

    g_bytPositiveFixed = 0x63;
    g_bytReverseFixed = 0x05;
    InitPositiveBox();
    InitReverseBox();
    printf("Positive box: \n%s\n",
           g_mtxPositiveBox.GetWrittenFormat().c_str());
    printf("Reverse box: \n%s\n",
           g_mtxReverseBox.GetWrittenFormat().c_str());
}

void InitOtherBox()
{
    g_polyModle = { 1, 0, 0, 1, 1, 1, 1, 1, 1 };
    PolynomialGF2 polyPositiveSeed = { 0, 1, 1, 1, 0, 1, 0, 1 };
    InitByteTransformMatrix(polyPositiveSeed, g_mtxBytePositiveTransformMatrix);

    PolynomialGF2 polyReverseSeed = { 0, 1, 0, 1, 0, 1, 1, 1 };
    InitByteTransformMatrix(polyReverseSeed, g_mtxByteReverseTransformMatrix);

    g_bytPositiveFixed = 0x28;
    g_bytReverseFixed = 0xA0;

    InitPositiveBox();
    InitReverseBox();
    printf("Positive box: \n%s\n",
           g_mtxPositiveBox.GetWrittenFormat().c_str());
    printf("Reverse box: \n%s\n",
           g_mtxReverseBox.GetWrittenFormat().c_str());
}

int main()
{
    // InitOtherBox();
    GetReverseTransfarmMatrix();
    system("pause");
    return 0;
}
