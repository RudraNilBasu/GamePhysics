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

    vec2() : x(0.0f), y(0.0f) {}

    vec2(float _x, float _y) : x(_x), y(_y) {}
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

    vec3() : x(0.0f), y(0.0f), z(0.0f) {}

    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
} vec3;

vec2 operator+(const vec2& l, const vec2& r);
vec2 operator-(const vec2& l, const vec2& r);
vec2 operator*(const vec2& l, const vec2& r);
vec2 operator*(const vec2& l, float r);
bool operator==(const vec2& l, const vec2& r);
bool operator!=(const vec2& l, const vec2& r);

vec3 operator+(const vec3& l, const vec3& r);
vec3 operator-(const vec3& l, const vec3& r);
vec3 operator*(const vec3& l, const vec3& r);
vec3 operator*(const vec3& l, float r);
bool operator==(const vec3& l, const vec3& r);
bool operator!=(const vec3& l, const vec3& r);

float Dot(const vec2& l, const vec2& r);
float Dot(const vec3& l, const vec2& r);

float Magnitude(const vec2& vec);
float Magnitude(const vec3& vec);

float MagnitudeSqr(const vec2& vec);
float MagnitudeSqr(const vec3& vec);

float Distance(const vec2& v1, const vec2& v2);
float Distance(const vec3& v1, const vec3& v2);

void Normalize(vec2& v);
void Normalize(vec3& v);

vec2 Normalized(const vec2& v);
vec3 Normalized(const vec3& v);

#endif
