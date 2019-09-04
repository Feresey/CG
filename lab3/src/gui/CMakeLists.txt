set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(gl win angle)

add_executable(${PROJECT_NAME} main.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

add_library(gui_lib gl/GLWidget.cpp gl/Draw.cpp gl/Interface.cpp gl/Shading.cpp
                    win/mainwindow.cpp angle/AngleSpinBox.cpp)

target_link_libraries(gui_lib Qt5::Widgets OpenGL::OpenGL core)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets OpenGL::OpenGL core gui_lib)
