#include "Geometry2D.h"

float Length(const Line2D& line)
{
    return Magnitude(line.end - line.start);
}

float LengthSqr(const Line2D& line)
{
    return MagnitudeSqr(line.end - line.start);
}

