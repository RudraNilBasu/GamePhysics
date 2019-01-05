#ifndef _H_2D_GEOMETRY_
#define _H_2D_GEOMETRY_

#include "vectors.h"
#include "matrices.h"

typedef struct vec2 Point2D;

typedef struct Line2D
{
    Point2D start;
    Point2D end;

    inline Line2D() : start(0.0f, 0.0f), end(0.0f, 0.0f) {}
    inline Line2D(const Point2D& _start, const Point2D& _end) :
        start(_start), end(_end) {}
} Line2D;

typedef struct Circle
{
    Point2D center;
    float radius;

    inline Circle() : radius(1.0f) {}
    inline Circle(const Point2D& _center, float _radius) :
        center(_center), radius(_radius) {}
} Circle;

typedef struct Rectangle2D
{
    vec2 origin;
    vec2 size;

    inline Rectangle2D() : origin(0.0f, 0.0f), size(1.0f, 0.0f) {}
    inline Rectangle2D(const vec2& _origin, const vec2& _size) :
        origin(_origin), size(_size) {}
} Rectangle2D;

typedef struct OrientedRectangle
{
    vec2 origin;
    vec2 halfExtents;
    float rotation;

    inline OrientedRectangle() :
        halfExtents(1.0f, 1.0f), rotation(0.0f) {}
    inline OrientedRectangle(const vec2& _origin,
                             const vec2& _halfExtents,
                             float _rotation):
        origin(_origin), halfExtents(_halfExtents),
        rotation(_rotation) {}
} OrientedRectangle;

float Length(const Line2D& line);
float LengthSqr(const Line2D& line);

vec2 GetMin(const Rectangle2D& rect);
vec2 GetMax(const Rectangle2D& rect);
Rectangle2D FromMinMax(const vec2& min, const vec2& max);

bool PointOnLine2D(const Point2D& point, const Line2D& line);
bool PointInCircle(const Point2D& point, const Circle& circle);
bool PointInRectangle2D(const Point2D& point,
        const Rectangle2D& rectangle);
bool PointInOrientedRectangle(const Point2D& point,
                              const OrientedRectangle& rectangle);

bool CircleLine(const Line2D& line, const Circle& circle);
#endif

