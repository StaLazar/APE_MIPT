#include "logic.h"

#include <ncurses.h>

/**
 * @brief Получить значение в пределах циклического диапазона.
 * @param value Оригинальное значение.
 * @param lower Нижняя граница диапазона.
 * @param upper Верхняя граница диапазона.
 * @retval value Оригинальное значение находится в диапазоне.
 * @retval upper Оригинальное значение меньше нижней границы.
 * @retval lower Оригинальное значение больше верхней границы.
 */
int clamp(const int value, const int lower, const int upper) {
    if (value < lower) {
        return upper;
    }
    if (value > upper) {
        return lower;
    }
    return value;
}

void initSnake(snake_type *snake) {
    snake->head.coords.y = (int)(MAX_TAIL_SIZE + 1UL);
    snake->head.coords.x = (int)(MAX_TAIL_SIZE + 1UL);
    snake->head.body.symbol = '0';
    snake->head.direction = direction_right;

    for (size_t i = 0UL; i < MAX_TAIL_SIZE; ++i) {
        snake->tail[i].coords.y = (int)(MAX_TAIL_SIZE + 1UL);
        snake->tail[i].coords.x = (int)(MAX_TAIL_SIZE - i);
        snake->tail[i].body.symbol = (i < MIN_TAIL_SIZE) ? 'O' : ' ';
    }

    snake->tailSize = MIN_TAIL_SIZE;
    snake->isInitialized = true;
}

void setSnakeDirection(snake_type *snake, const direction direction) {
    snake->head.direction = direction;
}

void moveSnake(snake_type *snake) {
    for (size_t i = MAX_TAIL_SIZE - 1UL; i > 0UL; --i) {
        snake->tail[i].coords.y = snake->tail[i - 1UL].coords.y;
        snake->tail[i].coords.x = snake->tail[i - 1UL].coords.x;
    }
    snake->tail[0].coords.y = snake->head.coords.y;
    snake->tail[0].coords.x = snake->head.coords.x;

    static const int minY = 0, minX = 0;
    switch (snake->head.direction) {
        case direction_left:
            snake->head.coords.x = clamp(--(snake->head.coords.x), minX, getmaxx(stdscr));
            break;
        case direction_right:
            snake->head.coords.x = clamp(++(snake->head.coords.x), minX, getmaxx(stdscr));
            break;
        case direction_up:
            snake->head.coords.y = clamp(--(snake->head.coords.y), minY, getmaxy(stdscr));
            break;
        case direction_down:
        default:
            snake->head.coords.y = clamp(++(snake->head.coords.y), minY, getmaxy(stdscr));
            break;
    }
}

void drawSnake(const snake_type *snake) {
    mvprintw(snake->head.coords.y, snake->head.coords.x, "%c", snake->head.body.symbol);

    for (size_t i = 0UL; i < MAX_TAIL_SIZE; ++i) {
        mvprintw(snake->tail[i].coords.y, snake->tail[i].coords.x, "%c", snake->tail[i].body.symbol);
    }
}

void initWindow() {
    initscr();
    curs_set(FALSE);
}

void closeWindow() {
    endwin();
}
