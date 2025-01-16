cmake_minimum_required(VERSION 3.25.0)
project(coursework VERSION 0.1.0 LANGUAGES C)

set(APPS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/apps)
set(COMMON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/common)
set(SENSORS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/sensors)
set(TOOLS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/tools)

add_subdirectory(apps)
add_subdirectory(common)
add_subdirectory(sensors)
add_subdirectory(tools)
