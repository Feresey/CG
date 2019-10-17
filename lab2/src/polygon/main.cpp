#include "Polygon.hpp"
#include <iostream>

int main()
{

    // (-91.068,0,-41.31) (-11.812,-86.501,-48.765) (112.72,124.69,-248.49)
    // (-91.068,0,-41.31) (-11.812,-86.501,-48.765) (0,0,0)
    // (-88.458,0,-46.639) (-3.5946,-80.337,-59.44) (118.19,160.57,-224.16)
    // (-88.458,0,-46.639) (-3.5946,-80.337,-59.44) (0,0,0)

    // (-83.48478699,0,-55.04807663) (10.9358902,-67.76474762,-72.7210083) (117.6686859,210.4953003,-178.4539337)
    // (-83.48478699,0,-55.04807663) (10.9358902,-67.76474762,-72.7210083) (0,0,0)

    // (-99.97015381,0,2.443228722) (-32.32178879,-74.98519135,-57.72801208) (-5.779025078,184.5331116,-236.4617157)
    // (-99.97015381,0,2.443228722) (-32.32178879,-74.98519135,-57.72801208) (0,0,0)
    Polygon a = { { -99.97015381f, 0.0f, 2.443228722f }, { -32.32178879f, -74.98519135f, -57.72801208f }, { -5.779025078f, 184.5331116f, -236.4617157f } },
            b = { { -99.97015381f, 0.0f, 2.443228722f }, { -32.32178879f, -74.98519135f, -57.72801208f }, { 0, 0, 0 } };
    std::cout << (a < b);

    return 0;
}