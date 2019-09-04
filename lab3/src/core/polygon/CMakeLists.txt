project(polygon LANGUAGES CXX)

set(SOURCES Polygon.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
