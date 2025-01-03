cmake_minimum_required(VERSION 3.25.0)

add_library(common
    timestamp.c
    vector.c
)

target_include_directories(common PUBLIC
    ${PROJECT_SOURCE_DIR}
)
