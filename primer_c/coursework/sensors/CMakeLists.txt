cmake_minimum_required(VERSION 3.25.0)

add_library(sensors
    temperature.c
)

target_include_directories(sensors PUBLIC
    ${PROJECT_SOURCE_DIR}
)
