include_directories(BEFORE
                    gl
                    polygon
                    matrix
                    mainwindow
                    vector)

add_executable(${PROJECT_NAME}
               main.cpp
               mainwindow/mainwindow.cpp
               gl/GLWidget.cpp
               gl/Draw.cpp
               gl/Interface.cpp
               vector/Vector.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
                      PRIVATE Qt5::Widgets
                              OpenGL::OpenGL
                              polygon
                              matrix)

add_subdirectory(polygon)
add_subdirectory(matrix)
