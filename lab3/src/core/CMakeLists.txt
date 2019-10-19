project(core LANGUAGES CXX)

# add_subdirectory(matrix)
# add_subdirectory(polygon)
# add_subdirectory(vector)
set(source matrix/Matrix.cpp matrix/Transform.cpp
    vector/Vector.cpp
    polygon/Polygon.cpp)

add_library(core STATIC ${source})