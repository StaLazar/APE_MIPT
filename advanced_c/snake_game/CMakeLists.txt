cmake_minimum_required(VERSION 3.25.0)
project(snake_game VERSION 0.1.0 LANGUAGES C)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    logic.c
    main.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CURSES_LIBRARIES}
)
