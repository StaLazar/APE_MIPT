cmake_minimum_required(VERSION 3.25.0)

add_library(sensors
    temperature.c
)

target_include_directories(sensors PUBLIC
    ${COMMON_SOURCE_DIR}
)

target_link_libraries(sensors PRIVATE
    common
)
