project(core LANGUAGES CXX)

set(STATIC_LIBRARIES vector polygon matrix figure)

add_subdirectory(vector)
add_subdirectory(polygon)
add_subdirectory(matrix)
add_subdirectory(figure)

add_library(core dummy.cpp)

target_link_libraries(${PROJECT_NAME} ${STATIC_LIBRARIES})
