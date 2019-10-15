set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

find_package(Qt5 COMPONENTS 3DCore)

add_library(matrix STATIC Matrix.cpp Transform.cpp)
# add_executable(test main.cpp) target_link_libraries(test PRIVATE Qt5::3DCore
# matrix)
target_link_libraries(matrix PRIVATE Qt5::3DCore polygon)
