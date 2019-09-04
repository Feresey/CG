project(vector LANGUAGES CXX)

set(SOURCES Vector2i.cpp Vector3f.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

if(${BUILD_TESTING})
    add_executable(test_cos main.cpp)
    target_link_libraries(test_cos vector)

    add_test(NAME Norm COMMAND test_cos "0 3 0" "3 0 0")
    set_tests_properties(Norm PROPERTIES PASS_REGULAR_EXPRESSION "^0\n$")

    add_test(NAME Same COMMAND test_cos "3 0 0" "3 0 0")
    set_tests_properties(Same PROPERTIES PASS_REGULAR_EXPRESSION "^1\n$")
endif()
