cmake_minimum_required(VERSION 3.15)

project(gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic\
    -Wno-sign-compare -Wno-long-long -Wctor-dtor-privacy\
    -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
    -Wconversion -Wsign-conversion -Wunreachable-code\
    -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

option(GIRO "Use giroscope to rotate image" OFF)
configure_file(config.h.in config.h @ONLY)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp mainwindow.cpp GLWidget.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
