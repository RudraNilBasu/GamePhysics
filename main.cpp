#include <stdio.h>
#include <iostream>

#include "vectors.h"
#include "Geometry2D.h"
#include "matrices.h"

int main()
{
    vec2 right = {1.0f, 0.0f};
    vec2 left = {-1.0f, 0.0f};
    vec2 ship_dir = {2.0f, 3.0f};
    std::cout << right.x << std::endl;
    std::cout << right[0] << std::endl;
    std::cout << (right + ship_dir).x << std::endl;
    std::cout << Dot(right, ship_dir) << std::endl;
    std::cout << MagnitudeSqr(ship_dir) << std::endl;
    std::cout << Magnitude(ship_dir) << std::endl;
    std::cout << Dot(ship_dir, ship_dir) << std::endl;
    std::cout << Distance(right, ship_dir) << std::endl;

    std::cout << RAD2DEG(Angle(right, left)) << std::endl;

    mat2 m2 = {1.0f, 0.0f,
               0.0f, -1.0f
    };
    std::cout << m2[1][1] << std::endl;

    std::cout << (right * 4).x << std::endl;
    std::cout << (right * 4).y << std::endl;

    // "test" out point and circle
    Point2D point1 = {0.0f, 0.0f};
    Point2D point2 = {1.0f, 1.0f};

    std::cout << "Length of line: " << Length(Line2D(point1, point2)) << std::endl;

    
    // Test point inside circle
    Point2D circle_origin = {0.0f, 0.0f};
    Circle c(circle_origin, 2.0f);
    Point2D inside_p = {1.0f, 0.0f};
    std::cout << PointInCircle(inside_p, c) << std::endl;
    inside_p = {-1.0f, 0.0f};
    std::cout << PointInCircle(inside_p, c) << std::endl;
    inside_p = {2.0f, 0.0f};
    std::cout << PointInCircle(inside_p, c) << std::endl;
    inside_p = {3.0f, 0.0f};
    std::cout << PointInCircle(inside_p, c) << std::endl;

    // Test Circle inside Circle
    Point2D c1_origin = {0.0f, 0.0f};
    Circle c1(c1_origin, 1.0f);
    Point2D c2_origin = {2.0f, 0.0f};
    Circle c2(c2_origin, 1.0f);
    std::cout << "Test Circle inside Circle" << std::endl;
    std::cout << c1_origin[0] << "," << c1_origin[1] << std::endl;
    std::cout << c2_origin[0] << "," << c2_origin[1] << std::endl;
    std::cout << CircleCircle(c1, c2) << std::endl;
    return 0;
}
