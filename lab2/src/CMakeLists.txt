include_directories(BEFORE
                    gl
                    ui
                    point
                    matrix
                    mainwindow)

add_executable(${PROJECT_NAME}
               main.cpp
               mainwindow/mainwindow.cpp
               gl/GLWidget.cpp
               point/pointview.cpp
               matrix/Matrix.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
                      PRIVATE Qt5::Widgets OpenGL::OpenGL pthread)
