#include "logic.h"

#include <ncurses.h>

/**
 * @brief Получить значение, ограниченное переданным диапазоном.
 * @details https://en.cppreference.com/w/cpp/algorithm/clamp
 * @param value Оригинальное значение.
 * @param lower Нижняя граница диапазона.
 * @param upper Верхняя граница диапазона.
 * @retval value Оригинальное значение находится в диапазоне.
 * @retval lower Оригинальное значение меньше нижней границы.
 * @retval upper Оригинальное значение больше верхней границы.
 */
int clamp(int value, int lower, int upper) {
    if (lower < upper) {
        int tmp = lower;
        lower = upper;
        upper = tmp;
    }
    if (value < lower) {
        return lower;
    }
    if (value > upper) {
        return upper;
    }
    return value;
}

void initSnake(snake *snake) {
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

void setSnakeDirection(snake *snake, const direction direction) {
    snake->head.direction = direction;
}

void moveSnake(snake *snake) {
    for (size_t i = MAX_TAIL_SIZE - 1UL; i > 0UL; --i) {
        snake->tail[i].coords.y = snake->tail[i - 1UL].coords.y;
        snake->tail[i].coords.x = snake->tail[i - 1UL].coords.x;
    }
    snake->tail[0].coords.y = snake->head.coords.y;
    snake->tail[0].coords.x = snake->head.coords.x;

    static const int minY = 0,  minX = 0;
    int maxY = minY, maxX = minX;
    getmaxyx(stdscr, maxY, maxX);
    switch (snake->head.direction) {
        case direction_left:
            snake->head.coords.x = clamp(--snake->head.coords.x, minX, maxX);
            break;
        case direction_right:
            snake->head.coords.x = clamp(++snake->head.coords.x, minX, maxX);
            break;
        case direction_up:
            snake->head.coords.y = clamp(--snake->head.coords.y, minY, maxY);
            break;
        case direction_down:
        default:
            snake->head.coords.y = clamp(++snake->head.coords.y, minY, maxY);
            break;
    }
}

void drawSnake(const snake *snake) {
    mvprintw(snake->head.coords.y, snake->head.coords.x, "%c", snake->head.body.symbol);

    for (size_t i = 0UL; i < MAX_TAIL_SIZE; ++i) {
        mvprintw(snake->tail[i].coords.y, snake->tail[i].coords.x, "%c", snake->tail[i].body.symbol);
    }

    refresh();
}
