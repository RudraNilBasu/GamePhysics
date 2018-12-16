#ifndef _H_MATH_MATRICES_
#define _H_MATH_MATRICES_

#include "vectors.h"

typedef struct mat2 {
    union {
        struct {
            float _11, _12,
                  _21, _22;
        };
        float asArray[4];
    };

    inline float* operator[](int i)
    {
        return &(asArray[i * 2]);
    }

    inline mat2()
    {
        _11 = _22 = 1.0f;
        _12 = _21 = 0.0f;
    }

    inline mat2(float f11, float f12, float f21, float f22)
    {
        _11 = f11; _12 = f12;
        _21 = f21; _22 = f22;
    }
}mat2;

typedef struct mat3 {
    union {
        struct {
            float _11, _12, _13,
                  _21, _22, _23,
                  _31, _32, _33;
        };
        float asArray[9];
    };

    inline float* operator[](int i)
    {
        return &(asArray[i * 3]);
    }

    inline mat3()
    {
        _11 = _22 = _33 = 1.0f;
        _12 = _13 = _21 = 0.0f;
        _31 = _32 = _23 = 0.0f;
    }

    inline mat3(float f11, float f12, float f13,
                float f21, float f22, float f23,
                float f31, float f32, float f33)
    {
        _11 = f11; _12 = f12; _13 = f13;
        _21 = f21; _22 = f22; _23 = f23;
        _31 = f31; _32 = f32; _33 = f33;
    }
}mat3;

typedef struct mat4 {
    union {
        struct {
            float _11, _12, _13, _14,
                  _21, _22, _23, _24,
                  _31, _32, _33, _34,
                  _41, _42, _43, _44;
        };
        float asArray[16];
    };

    inline float* operator[](int i)
    {
        return &(asArray[i * 4]);
    }

    inline mat4()
    {
        _11 = _22 = _33 = _44 = 1.0f;
        _12 = _13 = _14 = 0.0f;
        _21 = _23 = _24 = 0.0f;
        _31 = _32 = _34 = 0.0f;
        _41 = _42 = _43 = 0.0f;
    }

    inline mat4(float f11, float f12, float f13, float f14,
                float f21, float f22, float f23, float f24,
                float f31, float f32, float f33, float f34,
                float f41, float f42, float f43, float f44)
    {
        _11 = f11; _12 = f12; _13 = f13; _14 = f14;
        _21 = f21; _22 = f22; _23 = f23; _24 = f14;
        _31 = f31; _32 = f32; _33 = f33; _34 = f34;
        _41 = f41; _42 = f42; _43 = f43; _44 = f44;
    }
}mat4;

void Transpose(float* srcMatrix, float* destMatrix,
        int srcRows, int srcCols);
mat2 Transpose(const mat2& matrix);
mat3 Transpose(const mat3& matrix);
mat4 Transpose(const mat4& matrix);

/* Matrix multiplication by scalar */

mat2 operator*(const mat2& matrix, float scalar);
mat3 operator*(const mat3& matrix, float scalar);
mat4 operator*(const mat4& matrix, float scalar);

/* Matrix multiplication by matrix */

bool Multiply(const float* matA, int aRows, int aCols,
              const float* matB, int bRows, int bCols,
              const float* out
        );
mat2 operator*(const mat2& m1, const mat2& m2);
mat3 operator*(const mat3& m1, const mat3& m2);
mat4 operator*(const mat4& m1, const mat4& m2);

float Determinant(const mat2& matrix);
mat2 Cut(const mat3& source, int x, int y);
mat3 Minor(const mat3& matrix);
mat2 Minor(const mat2& matrix);

void Cofactor(const float* matrix, int row, int col);
mat2 Cofactor(const mat2& matrix);
mat3 Cofactor(const mat3& matrix);

#endif

