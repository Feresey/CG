project(core LANGUAGES CXX)

# add_subdirectory(matrix) add_subdirectory(polygon) add_subdirectory(vector)
set(source
    matrix/Matrix.cpp
    matrix/Transform.cpp
    vector/Vector.cpp
    polygon/Polygon.cpp
    figure/Figure.cpp)

add_library(core STATIC ${source})

pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
                      ANALYZE ${PROJECT_NAME}
                      OUTPUT FORMAT tasklist
                      LOG ${PROJECT_NAME}.err)

