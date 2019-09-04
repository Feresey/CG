project(matrix LANGUAGES CXX)

set(SOURCES Matrix.cpp Transform.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
