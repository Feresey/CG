set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

find_package(Qt5 COMPONENTS 3DCore)

add_library(polygon STATIC Polygon.cpp)
target_link_libraries(polygon PRIVATE Qt5::3DCore)

# add_executable(test1 main.cpp)

# target_link_libraries(test1
#                       ${Boost_LIBRARIES}
#                       Qt5::3DCore
#                       polygon)

# add_test(NAME Test1 COMMAND test1)
