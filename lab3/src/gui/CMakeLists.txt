set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(gl win)

add_executable(${PROJECT_NAME}
               main.cpp
               gl/GLWidget.cpp
               gl/Draw.cpp
               gl/Interface.cpp
               win/mainwindow.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
                      PRIVATE Qt5::Widgets
                              OpenGL::OpenGL
                              core)

