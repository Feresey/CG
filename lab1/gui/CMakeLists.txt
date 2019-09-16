cmake_minimum_required(VERSION 3.5)

project(gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

option(POLAR "Change decart coordinates to polar" ON)
configure_file(config.h.in config.h @ONLY)

add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp oglwidget.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE GLU)
