set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

add_library(matrix STATIC Matrix.cpp Transform.cpp)
target_link_libraries(matrix PRIVATE polygon vector)
