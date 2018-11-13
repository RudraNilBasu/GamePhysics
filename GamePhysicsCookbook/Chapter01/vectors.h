#ifndef _H_MATH_VECTORS_
#define _H_MATH_VECTORS_

typedef struct vec2 {
    union {
        struct {
            float x;
            float y;
        };
        float asArray[2];
    };

    float& operator[](int i)
    {
        return asArray[i];
    }
} vec2;

typedef struct vec3 {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float asArray[3];
    };

    float& operator[](int i)
    {
        return asArray[i];
    }
} vec3;

vec2 operator+(const vec2& l, const vec2& r);
vec2 operator-(const vec2& l, const vec2& r);
vec2 operator*(const vec2& l, const vec2& r);
vec2 operator==(const vec2& l, const vec2& r);
vec2 operator!=(const vec2& l, const vec2& r);

vec3 operator+(const vec3& l, const vec3& r);
vec3 operator-(const vec3& l, const vec3& r);
vec3 operator*(const vec3& l, const vec3& r);
vec3 operator==(const vec3& l, const vec3& r);
vec3 operator!=(const vec3& l, const vec3& r);

#endif
