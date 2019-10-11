find_package(Qt5 COMPONENTS Widgets 3DCore)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

add_library(polygon STATIC Polygon.cpp)
add_executable(test main.cpp)

target_link_libraries(test PRIVATE Qt5::Widgets polygon)
target_link_libraries(polygon PRIVATE Qt5::Widgets)
