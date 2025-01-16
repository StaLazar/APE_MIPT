cmake_minimum_required(VERSION 3.25.0)
project(sensalyzer VERSION 0.1.0 LANGUAGES C)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    sensalyzer.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${COMMON_SOURCE_DIR}
    ${SENSORS_SOURCE_DIR}
    ${TOOLS_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    common
    sensors
    tools
)
