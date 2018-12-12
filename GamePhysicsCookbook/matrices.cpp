#include "matrices.h"

/* For details on the float comparison, check
 * http://realtimecollisiondetection.net/pubs/Tolerances/
 */
#define FLOAT_CMP(x, y)   \
    (fabsf((x) - (y)) <= FLT_EPSILON * \
     fmaxf(1.0f,    \
         fmaxf(fabsf(x), fabsf(y)))    \
     )

void Transpose(const float* srcMatrix, float* destMatrix,
        int srcRows, int srcCols)
{
    for (int i = 0; i < (srcRows * srcCols); i++)
    {
        int row = i / srcRows;
        int col = i % srcCols;
        destMatrix[i] = srcMatrix[srcCols * col + row];
    }
}

mat2 Transpose(const mat2& matrix)
{
    mat2 mT;
    Transpose(matrix.asArray, mT.asArray, 2, 2);
    return mT;
}

mat3 Transpose(const mat3& matrix)
{
    mat3 mT;
    Transpose(matrix.asArray, mT.asArray, 3, 3);
    return mT;
}

mat4 Transpose(const mat4& matrix)
{
    mat4 mT;
    Transpose(matrix.asArray, mT.asArray, 4, 4);
    return mT;
}

