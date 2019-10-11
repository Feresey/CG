#include "Polygon.hpp"
#include <iostream>

int main()
{
    Polygon a = std::vector<QVector3D>{ QVector3D{ 0, 0, 0 }, QVector3D{ 4, 0, 0 }, QVector3D{ 2, 2, 0 } },
            b = { { 1, -1, 0 }, { 3, -1, 0 }, { 2, 1, 0 } };
    std::cout << (a < b);

    return 0;
}
