#include "Matrix.hpp"
#include <iostream>

int main()
{
    Matrix
        a{
            {
                // 1, 0, 0, 0,
                // 0, 1, 0, 0,
                // 0, 0, 1, 0,
                0, 0, 0, 0.5 //
            },
            1, 4
        },
        b{
            {
                0, 0, 1, 0,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16 //
            },
            4, 4
        };

    Matrix res = a * b;
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j)
            std::cout << res(i, j) << "\t\t";
        std::cout << '\n';
    }

    return 0;
}
