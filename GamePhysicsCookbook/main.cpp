#include <stdio.h>
#include <iostream>

#include "vectors.h"
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
    return 0;
}