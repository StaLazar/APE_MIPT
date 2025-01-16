cmake_minimum_required(VERSION 3.25.0)

add_library(common
    timestamp.c
    vector.c
)

target_link_libraries(common PRIVATE
    m
)
