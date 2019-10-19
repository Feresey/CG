cmake_minimum_required(VERSION 3.0)

project(lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic\
    -Wno-sign-compare -Wno-long-long -Wctor-dtor-privacy\
    -Wnon-virtual-dtor -Wold-style-cast -Winit-self\
    -Wconversion -Wsign-conversion -Wunreachable-code\
    -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

# enable_testing()
# find_package(Boost REQUIRED)

add_subdirectory(src)
