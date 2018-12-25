#include "vectors.h"

#include <cmath>
#include <cfloat>

/* For details on the float comparison, check
 * http://realtimecollisiondetection.net/pubs/Tolerances/
 */
#define FLOAT_CMP(x, y)   \
    (fabsf((x) - (y)) <= FLT_EPSILON * \
     fmaxf(1.0f,    \
         fmaxf(fabsf(x), fabsf(y)))    \
     )

vec2 operator+(const vec2& l, const vec2& r)
{
    return {l.x + r.x, l.y + r.y};
}

vec2 operator-(const vec2& l, const vec2& r)
{
    return {l.x - r.x, l.y - r.y};
}

vec2 operator*(const vec2& l, const vec2& r)
{
    return {l.x * r.x, l.y * r.y};
}

vec2 operator*(const vec2& l, float r)
{
    return {l.x * r, l.y * r};
}

bool operator==(const vec2& l, const vec2& r)
{
    return FLOAT_CMP(l.x, r.x) && FLOAT_CMP(l.y, r.y);
}

bool operator!=(const vec2& l, const vec2& r)
{
    return !(l == r);
}

vec3 operator+(const vec3& l, const vec3& r)
{
    return {l.x + r.x, l.y + r.y, l.z + r.z};
}

vec3 operator-(const vec3& l, const vec3& r)
{
    return {l.x - r.x, l.y - r.y, l.z - r.z};
}

vec3 operator*(const vec3& l, const vec3& r)
{
    return {l.x * r.x, l.y * r.y, l.z * r.z};
}

vec3 operator*(const vec3& l, float r)
{
    return {l.x * r, l.y * r, l.z * r};
}

bool operator==(const vec3& l, const vec3& r)
{
    return FLOAT_CMP(l.x, r.x) && FLOAT_CMP(l.y, r.y) && FLOAT_CMP(l.z, r.z);
}

bool operator!=(const vec3& l, const vec3& r)
{
    return !(l == r);
}

float Dot(const vec2& l, const vec2& r)
{
    return (l.x * r.x) + (l.y * r.y);
}

float Dot(const vec3& l, const vec3& r)
{
    return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
}

float Magnitude(const vec2& vec)
{
    return sqrtf(Dot(vec, vec));
}

float Magnitude(const vec3& vec)
{
    return sqrtf(Dot(vec, vec));
}

float MagnitudeSqr(const vec2& vec)
{
    return Dot(vec, vec);
}

float MagnitudeSqr(const vec3& vec)
{
    return Dot(vec, vec);
}

float Distance(const vec2& v1, const vec2& v2)
{
    return Magnitude(v1 - v2);
}

float Distance(const vec3& v1, const vec3& v2)
{
    return Magnitude(v1 - v2);
}

void Normalize(vec2& v)
{
    v = v * (1.0f / Magnitude(v));
}

void Normalize(vec3& v)
{
    v = v * (1.0f / Magnitude(v));
}

vec2 Normalized(const vec2& v)
{
    return v * (1.0f / Magnitude(v));
}

vec3 Normalized(const vec3& v)
{
    return v * (1.0f / Magnitude(v));
}

vec3 Cross(const vec3& l, const vec3& r)
{
    vec3 result;
    result.x = (l.y * r.z) - (l.z - r.y);
    result.y = (l.z * r.x) - (l.x - r.z);
    result.z = (l.x * r.y) - (l.y - r.x);
    return result;
}

float Angle(const vec2& l, const vec2& r)
{
    // cos theta = Dot(a, b) / |a||b|
    float m = sqrtf(MagnitudeSqr(l) * MagnitudeSqr(r));
    return acos(Dot(l, r) / m);
}

float Angle(const vec3& l, const vec3& r)
{
    float m = sqrtf(MagnitudeSqr(l) * MagnitudeSqr(r));
    return acos(Dot(l, r) / m);
}

vec2 Project(const vec2&len, const vec2& dir)
{
    // |A|cos theta * unit vector of B
    // |A|cos theta * (B / |B|)
    // (|A| |B| cos theta) * (B / |B|^2)
    // ((A.B) * B) / |B|^2
    vec2 proj = (dir * Dot(len, dir)) * (1.0f / (MagnitudeSqr(dir)));
    return proj;
}

vec2 Perpendicular(const vec2&len, const vec2& dir)
{
    return len - Project(len, dir);
}

vec3 Project(const vec3&len, const vec3& dir)
{
    vec3 proj = (dir * Dot(len, dir)) * (1.0f / (MagnitudeSqr(dir)));
    return proj;
}

vec3 Perpendicular(const vec3&len, const vec3& dir)
{
    return len - Project(len, dir);
}

vec2 Reflection(const vec2& vec, const vec2& normal)
{
    return vec - (Project(vec, normal)) * 2;
}

vec3 Reflection(const vec3& vec, const vec3& normal)
{
    return vec - (Project(vec, normal)) * 2;
}

