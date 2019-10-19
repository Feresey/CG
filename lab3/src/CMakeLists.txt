set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}
        CACHE PATH
        "Single Directory for all"
    )

include_directories(BEFORE include)

add_subdirectory(core)
add_subdirectory(gui)
