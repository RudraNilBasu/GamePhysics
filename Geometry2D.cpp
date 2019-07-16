#include "Geometry2D.h"
#include "matrices.h"

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

float Length(const Line2D& line)
{
    return Magnitude(line.end - line.start);
}

float LengthSqr(const Line2D& line)
{
    return MagnitudeSqr(line.end - line.start);
}

vec2 GetMin(const Rectangle2D& rect)
{
    vec2 p1 = rect.origin;
    vec2 p2 = p1 + rect.size;

    return vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
}

vec2 GetMax(const Rectangle2D& rect)
{
    vec2 p1 = rect.origin;
    vec2 p2 = p1 + rect.size;

    return vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
}

Rectangle2D FromMinMax(const vec2& min, const vec2& max)
{
    return Rectangle2D(min, max - min);
}

bool PointOnLine2D(const Point2D& point, const Line2D& line)
{
    float dy = line.end.y - line.start.y;
    float dx = line.end.x - line.start.x;
    float m = (dy * 1.0f) / dx; // slope

    // y intercept
    float c = line.end.y - (m * line.end.x);
    return FLOAT_CMP(point.y, ((m * point.x) + c));
    // vec2 start = line.start;
    // vec2 end = line.end;
    // float sl_line = (1.0f * (end.y - start.y)) / (end.x - start.x);
    // float sl_pt_line = (1.0f * (end.y - point.y)) / (end.x - point.x);
    // return FLOAT_CMP(sl_line, sl_pt_line);
}

bool PointInCircle(const Point2D& point, const Circle& circle)
{
    return MagnitudeSqr(point - circle.center) <
        (circle.radius * circle.radius);
}

bool PointInRectangle2D(const Point2D& point,
        const Rectangle2D& rectangle)
{
    vec2 min = GetMin(rectangle);
    vec2 max = GetMax(rectangle);

    return point.x >= min.x &&
           point.y >= min.y &&
           point.x <= max.x &&
           point.y <= max.y;
}

bool PointInOrientedRectangle(const Point2D& point,
                              const OrientedRectangle& rectangle)
{
    vec2 rotVector = point - rectangle.origin;
    float theta = rectangle.rotation;

    float zRotation2x2[] = {
        cosf(theta), sinf(theta),
        -sinf(theta), cosf(theta)
    };

    Multiply(
            vec2(rotVector.x, rotVector.y).asArray,
            1, 2,
            zRotation2x2,
            2, 2,
            rotVector.asArray);
    Rectangle2D localRectangle(Point2D(),
            rectangle.halfExtents * 2.0f);
    vec2 localPoint = rotVector + rectangle.halfExtents;
    return PointInRectangle2D(localPoint, localRectangle);
}

bool CircleLine(const Line2D& line, const Circle& circle)
{
    vec2 ab = line.end - line.start;
    float t = Dot(circle.center - line.start, ab) / Dot(ab, ab);

    if (t < 0.0f || t > 0.0f) {
        return false;
    }

    Point2D closestPoint = line.start + ab * t;
    Line2D circleToClosest(circle.center, closestPoint);
    return LengthSqr(circleToClosest) < (circle.radius * circle.radius);
}

bool LineRectangle(const Line2D& line,
                   const Rectangle2D& rect)
{
    if (PointInRectangle2D(line.start, rect) ||
        PointInRectangle2D(line.end, rect)) {
        return true;
    }

    vec2 norm = Normalized(line.end - line.start);
    norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;
    norm.y = (norm.y != 0) ? 1.0f / norm.y : 0;
    vec2 min = (GetMin(rect) - line.start) * norm;
    vec2 max = (GetMax(rect) - line.start) * norm;

    float tmin = fmaxf(fminf(min.x, max.x), fminf(min.y, max.y));
    float tmax = fminf(fmaxf(min.x, max.x), fmaxf(min.y, max.y));
    if (tmax < 0 || tmin > tmax) {
        return false;
    }
    float t = (tmin < 0.0f) ? tmax : tmin;
    return t > 0.0f && t * t < LengthSqr(line);

}

bool LineOrientedRectangle(const Line2D& line,
        const OrientedRectangle& rectangle) {
    float theta = -DEG2RAD(rectangle.rotation);
    float zRotation2x2[] = {
        cosf(theta), sinf(theta),
        -sinf(theta), cosf(theta) };
    Line2D localLine;

    vec2 rotVector = line.start - rectangle.origin;
    Multiply(vec2(rotVector.x, rotVector.y).asArray,
            1, 2,
            zRotation2x2,
            2, 2, rotVector.asArray);
    localLine.start  = rotVector + rectangle.halfExtents;
    rotVector = line.end - rectangle.origin;
    Multiply(vec2(rotVector.x, rotVector.y).asArray,
             1, 2,
             zRotation2x2,
             2, 2,
             rotVector.asArray);
    localLine.end = rotVector + rectangle.halfExtents;
    Rectangle2D localRectangle(Point2D(), rectangle.halfExtents * 2.0f);
    return LineRectangle(localLine, localRectangle);
}

bool CircleCircle(const Circle& c1, const Circle& c2)
{
    float center_distance_sq = MagnitudeSqr(c1.center - c2.center);
    float distance_sq = (c1.radius + c2.radius) * (c1.radius + c2.radius);

    return (distance_sq >= center_distance_sq);
}

