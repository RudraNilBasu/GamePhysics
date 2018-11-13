#include "vectors.h"

#include <cmath>
#include <cfloat>

/* For details on the float comparison, check
 * http://realtimecollisiondetection.net/pubs/Tolerances/
 */
#define FLOAT_CMP(x, y)   \
    (fabsf((x) - (y)) <= FLT_EPSILON * \
     fmaxf(1.0f,    \
         fmaxf(fbasf(x), fabsf(y)))    \
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

vec2 operator==(const vec2& l, const vec2& r)
{
    return FLOAT_CMP(l.x, r.x) && FLOAT_CMP(l.y, r.y);
}

vec2 operator!=(const vec2& l, const vec2& r)
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

vec3 operator==(const vec3& l, const vec3& r)
{
    return FLOAT_CMP(l.x, r.x) && FLOAT_CMP(l.y, r.y) && FLOAT_CMP(l.z, r.z);
}

vec3 operator!=(const vec3& l, const vec3& r)
{
    return !(l == r);
}

