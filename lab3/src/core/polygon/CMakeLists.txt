set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

add_library(polygon STATIC Polygon.cpp)
target_link_libraries(polygon PRIVATE vector)
