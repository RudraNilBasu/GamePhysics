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
}mat4;

void Transpose(float* srcMatrix, float* destMatrix,
        int srcRows, int srcCols);
mat2 Transpose(const mat2& matrix);
mat3 Transpose(const mat3& matrix);
mat4 Transpose(const mat4& matrix);

#endif

