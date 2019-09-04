project(figure LANGUAGES CXX)

set(SOURCES Figure.cpp Iter.cpp cylinder.cpp)

add_library(${PROJECT_NAME} OBJECT ${SOURCES})
