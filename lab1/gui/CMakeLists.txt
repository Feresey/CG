cmake_minimum_required(VERSION 3.5)

project(gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_COMPILER zapcc)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

add_compile_options(-O2 -Wall -Wextra -Wpedantic)
add_executable(gui
               main.cpp
               mainwindow.cpp
               mainwindow.h
               oglwidget.cpp
               oglwidget.h
               mainwindow.ui)

target_link_libraries(gui PRIVATE Qt5::Widgets)
target_link_libraries(gui PRIVATE Qt5::OpenGL)
target_link_libraries(gui PRIVATE OpenGL::OpenGL)
target_link_libraries(gui PRIVATE GLU)

