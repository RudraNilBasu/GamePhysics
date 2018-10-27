#include <stdio.h>
#include <iostream>

#include "vectors.h"

int main()
{
    vec2 right = {1.0f, 0.0f};
    std::cout << right.x << std::endl;
    std::cout << right[0] << std::endl;
    return 0;
}
