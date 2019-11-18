project(core LANGUAGES CXX)

set(source
    matrix/Matrix.cpp
    matrix/Transform.cpp
    vector/Vector.cpp
    polygon/Polygon.cpp
    figure/Figure.cpp
    figure/Iter.cpp)

add_library(core STATIC ${source})
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
                        ANALYZE ${PROJECT_NAME}
                        OUTPUT FORMAT tasklist
                        LOG ${PROJECT_NAME}.err)
endif()

