#include "Vector.hpp"

#include <iostream>
#include <sstream>

Vector3f scan(std::stringstream& s)
{
    Vector3f res;
    s >> res[0] >> res[1] >> res[2];
    return res;
}

int main(int argc, char** argv)
{
    if (argc != 3)
        return 1;
    std::stringstream ain(argv[1]), bin(argv[2]);
    Vector3f a(scan(ain)), b(scan(bin));

    std::cout << a.Angle(b);
}