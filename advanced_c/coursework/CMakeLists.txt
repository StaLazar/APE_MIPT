cmake_minimum_required(VERSION 3.25.0)
project(calcularea VERSION 1.0.0 LANGUAGES C)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    algorithm.c
    common.c
    main.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    m
)
