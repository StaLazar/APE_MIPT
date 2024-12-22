cmake_minimum_required(VERSION 3.25.0)
project(sensalyzer VERSION 0.1.0 LANGUAGES C)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/main.c
)

add_subdirectory(sensors)
add_subdirectory(tools)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sensors
    tools
)
