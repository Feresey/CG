cmake_minimum_required(VERSION 3.5)

project(gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_link_options(-lGLX_mesa -lGLX -lglut -lGLU)
add_compile_options(-g3 -Wall -Wextra -Wpedantic)
add_executable(gui
               main.cpp
               mainwindow.cpp
               mainwindow.h
               oglwidget.cpp
               oglwidget.h
               mainwindow.ui)

target_link_libraries(gui PRIVATE Qt5::Widgets)
