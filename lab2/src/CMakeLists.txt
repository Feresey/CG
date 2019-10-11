include_directories(BEFORE
                    gl
                    ui
                    polygon
                    matrix
                    mainwindow
                    vector3i)

add_subdirectory(polygon)

add_executable(${PROJECT_NAME}
               main.cpp
               mainwindow/mainwindow.cpp
               gl/GLWidget.cpp
               gl/Draw.cpp
               gl/Interface.cpp
               matrix/Matrix.cpp
               vector3i/Vector3I.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
                      PRIVATE Qt5::Widgets
                              OpenGL::OpenGL
                              polygon)
