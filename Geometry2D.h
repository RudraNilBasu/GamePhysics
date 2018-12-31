#ifndef _H_2D_GEOMETRY_
#define _H_2D_GEOMETRY_

#include "vectors.h"

typedef struct vec2 Point2D;

typedef struct Line2D
{
    Point2D start;
    Point2D end;

    inline Line2D() : start(0.0f, 0.0f), end(0.0f, 0.0f) {}
    inline Line2D(const Point2D& _start, const Point2D& _end) : start(_start.x, _start.y), end(_end.x, _end.y) {}
} Line2D;

float Length(const Line2D& line);
float LengthSqr(const Line2D& line);

#endif

