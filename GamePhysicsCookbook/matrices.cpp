#include "matrices.h"

#include <cmath>
#include <float.h>

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

mat2 operator*(const mat2& matrix, float scalar)
{
    mat2 result;
    for (int i = 0; i < 4; i++) {
        result.asArray[i] = matrix.asArray[i] * scalar;
    }
    return result;
}

mat3 operator*(const mat3& matrix, float scalar)
{
    mat3 result;
    for (int i = 0; i < 9; i++) {
        result.asArray[i] = matrix.asArray[i] * scalar;
    }
    return result;
}

mat4 operator*(const mat4& matrix, float scalar)
{
    mat4 result;
    for (int i = 0; i < 16; i++) {
        result.asArray[i] = matrix.asArray[i] * scalar;
    }
    return result;
}

bool Multiply(const float* matA, int aRows, int aCols,
              const float* matB, int bRows, int bCols,
              float* out
        )
{
    if (aCols != bRows)
        return false;

    for (int i = 0; i < aRows; i++) {
        for (int j = 0; j < bCols; j++) {
            float sum = 0.0f;
            for (int k = 0; k < aCols; k++) {
                int x = i * aCols + k;
                int y = k * bCols + j;
                sum += (matA[x] * matB[y]);
            }
            out[i * bCols + j] = sum;
        }
    }
    return true;
}

mat2 operator*(const mat2& m1, const mat2& m2)
{
    mat2 result;
    Multiply(m1.asArray, 2, 2, m2.asArray, 2, 2, result.asArray);
    return result;
}

mat3 operator*(const mat3& m1, const mat3& m2)
{
    mat3 result;
    Multiply(m1.asArray, 3, 3, m2.asArray, 3, 3, result.asArray);
    return result;
}

mat4 operator*(const mat4& m1, const mat4& m2)
{
    mat4 result;
    Multiply(m1.asArray, 4, 4, m2.asArray, 4, 4, result.asArray);
    return result;
}

float Determinant(const mat2& matrix)
{
    return (matrix._11 * matrix._22) -
           (matrix._21 * matrix._12);
}

float Determinant(const mat3& matrix)
{
    float result = 0.0f;
    mat3 cofactor = Cofactor(matrix);
    for (int i = 0; i < 3; i++) {
        int index = 3 * 0 + i;
        result += (matrix.asArray[index] * cofactor[0][i]);
    }
    return result;
}

float Determinant(const mat4& matrix)
{
    float result = 0.0f;
    mat4 cofactor = Cofactor(matrix);
    for (int i = 0; i < 4; i++) {
        int index = 4 * 0 + i;
        result += (matrix.asArray[index] * cofactor[0][i]);
    }
    return result;
}

mat2 Cut(const mat3& source, int x, int y)
{
    int index = 0;
    mat2 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == x || j == y)
                continue;
            result.asArray[index++] = source.asArray[i * 3 + j];
        }
    }
    return result;
}

mat3 Cut(const mat4& source, int x, int y)
{
    int index = 0;
    mat3 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == x || j == y)
                continue;
            result.asArray[index++] = source.asArray[i * 4 + j];
        }
    }
    return result;
}

mat4 Minor(const mat4& matrix)
{
    mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.asArray[i * 4 + j] = Determinant(Cut(matrix, i, j));
        }
    }
    return result;
}

mat3 Minor(const mat3& matrix)
{
    mat3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.asArray[i * 3 + j] = Determinant(Cut(matrix, i, j));
        }
    }
    return result;
}

mat2 Minor(const mat2& matrix)
{
    return mat2(matrix._22, matrix._21,
                matrix._12, matrix._11);
}

void Cofactor(float* out, const float* minor, int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            float sign = powf(-1, i + j);
            // TODO: Is this out[i][j] or out[j][i] ???
            out[i * col + j] = minor[i * col + j] * sign;
        }
    }
}

mat2 Cofactor(const mat2& matrix)
{
    mat2 result;
    Cofactor(result.asArray, matrix.asArray, 2, 2);
    return result;
}

mat3 Cofactor(const mat3& matrix)
{
    mat3 result;
    Cofactor(result.asArray, matrix.asArray, 3, 3);
    return result;
}

mat4 Cofactor(const mat4& matrix)
{
    mat4 result;
    Cofactor(result.asArray, matrix.asArray, 4, 4);
    return result;
}

mat2 Adjugate(const mat2& matrix)
{
    return Transpose(Cofactor(matrix));
}

mat3 Adjugate(const mat3& matrix)
{
    return Transpose(Cofactor(matrix));
}

mat4 Adjugate(const mat4& matrix)
{
    return Transpose(Cofactor(matrix));
}

mat2 Inverse(const mat2& matrix)
{
    // Adjugate / Determinant
    float det = Determinant(matrix);
    if (FLOAT_CMP(det, 0.0f)) { return mat2(); }
    return Adjugate(matrix) * (1.0f / det);
}

mat3 Inverse(const mat3& matrix)
{
    float det = Determinant(matrix);
    if (FLOAT_CMP(det, 0.0f)) { return mat3(); }
    return Adjugate(matrix) * (1.0f / det);
}

mat4 Inverse(const mat4& matrix)
{
    float det = Determinant(matrix);
    if (FLOAT_CMP(det, 0.0f)) { return mat4(); }
    return Adjugate(matrix) * (1.0f / det);
}

mat4 Translation(float x, float y, float z)
{
    return mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            x,    y,    z,    1.0f
    );
}

mat4 Translation(const vec3& pos)
{
    return mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            pos.x, pos.y, pos.z, 1.0f
    );
}

vec3 GetTranslation(mat4 matrix)
{
    return vec3(matrix._41, matrix._42, matrix._43);
}

mat4 Scale(float x, float y, float z)
{
    return mat4(
            x,    0.0f, 0.0f, 0.0f,
            0.0f, y,    0.0f, 0.0f,
            0.0f, 0.0f, z,    0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 Scale(const vec3& vec)
{
    return mat4(
            vec.x, 0.0f, 0.0f, 0.0f,
            0.0f, vec.y, 0.0f, 0.0f,
            0.0f, 0.0f, vec.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    );
}

vec3 GetScale(mat4 matrix)
{
    return vec3(matrix._11, matrix._22, matrix._33);
}

mat4 Rotation(float pitch, float yaw, float roll)
{
    return ZRotation(roll) *
           XRotation(pitch) *
           YRotation(yaw);
}

mat3 Rotation3x3(float pitch, float yaw, float roll)
{
    return ZRotation3x3(roll) *
           XRotation3x3(pitch) *
           YRotation3x3(yaw);
}

mat4 ZRotation(float angle)
{
    angle = DEG2RAD(angle);
    return mat4(
            cosf(angle),  sinf(angle), 0.0f, 0.0f,
            -sinf(angle), cosf(angle), 0.0f, 0.0f,
            0.0f,         0.0f,        1.0f, 0.0f,
            0.0f,         0.0f,        0.0f, 1.0f
            );
}

mat3 ZRotation3x3(float angle)
{
    angle = DEG2RAD(angle);
    return mat3(
            cosf(angle),  sinf(angle), 0.0f,
            -sinf(angle), cosf(angle), 0.0f,
            0.0f,         0.0f,        1.0f
            );
}

mat4 YRotation(float angle)
{
    angle = DEG2RAD(angle);
    return mat4(
            cosf(angle),  0.0f, -sinf(angle), 0.0f,
            0.0f,         1.0f,        0.0f,  0.0f,
            sinf(angle),  0.0f, cosf(angle),  0.0f,
            0.0f,         0.0f, 0.0f,         1.0f
            );
}

mat3 YRotation3x3(float angle)
{
    angle = DEG2RAD(angle);
    return mat3(
            cosf(angle),  0.0f, -sinf(angle),
            0.0f,         1.0f,        0.0f,
            sinf(angle),  0.0f, cosf(angle)
            );
}

mat4 XRotation(float angle)
{
    angle = DEG2RAD(angle);
    return mat4(
            1.0f, 0.0f,         0.0f,          0.0f,
            0.0f, cosf(angle),  sinf(angle),   0.0f,
            0.0f, -sinf(angle), cosf(angle),   0.0f,
            0.0f, 0.0f,          0.0f,         1.0f
            );
}

mat3 XRotation3x3(float angle)
{
    angle = DEG2RAD(angle);
    return mat3(
            1.0f, 0.0f,         0.0f,
            0.0f, cosf(angle),  sinf(angle),
            0.0f, -sinf(angle), cosf(angle)
            );
}

mat4 AxisAngle(const vec3& axis, float angle)
{
    angle = DEG2RAD(angle);
    float s = sinf(angle);
    float c = cosf(angle);
    float t = 1 - s;

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    if (!FLOAT_CMP(MagnitudeSqr(axis), 1.0f)) {
        float inv_len = 1.0f / Magnitude(axis);

        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
    }

    return mat4(
            (t * x * x) + c, (t * x * y) + (s * z), (t * x* z) + (s * y), 0.0f,
            (t * x * y) + (s * z), (t * y * y) + c, (t * y * z) + (s * x), 0.0f,
            (t * x * y) + (s * y), (t * y * z) + (s * x), (t * z * z) + c, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
            );
}

mat3 AxisAngle3x3(const vec3& axis, float angle)
{
    angle = DEG2RAD(angle);
    float s = sinf(angle);
    float c = cosf(angle);
    float t = 1 - s;

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    if (!FLOAT_CMP(MagnitudeSqr(axis), 1.0f)) {
        float inv_len = 1.0f / Magnitude(axis);

        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
    }

    return mat3(
            (t * x * x) + c, (t * x * y) + (s * z), (t * x* z) + (s * y),
            (t * x * y) + (s * z), (t * y * y) + c, (t * y * z) + (s * x),
            (t * x * y) + (s * y), (t * y * z) + (s * x), (t * z * z) + c
            );
}

