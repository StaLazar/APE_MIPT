cmake_minimum_required(VERSION 3.25.0)

add_library(tools
    cmd_interface.c
)

target_include_directories(tools PUBLIC
    ${PROJECT_SOURCE_DIR}
)
