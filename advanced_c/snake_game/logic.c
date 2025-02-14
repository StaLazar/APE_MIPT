#include "logic.h"

#include <ncurses.h>

//! Количество направлений, доступных для выбора с помощью клавиш.
#define DIR_WAYS 4UL
//! Количество клавиш, определяющих одно и то же направление.
#define DIR_KEYS 3UL

/**
 * @brief Получить значение в пределах циклического диапазона.
 * @param[in] value Оригинальное значение.
 * @param[in] lower Нижняя граница диапазона.
 * @param[in] upper Верхняя граница диапазона.
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
    snake->head.coords.y = (int)(START_COORD_Y);
    snake->head.coords.x = (int)(START_COORD_X);
    snake->head.body.symbol = BODY_HEAD;
    snake->head.direction = direction_right;

    for (size_t i = 0UL; i < MAX_TAIL_SIZE; ++i) {
        snake->tail[i].coords.y = (int)(START_COORD_Y);
        snake->tail[i].coords.x = (int)(START_COORD_X - 1UL - i);
        snake->tail[i].body.symbol = (i < MIN_TAIL_SIZE) ? BODY_TAIL : BODY_IDLE;
    }

    snake->tailSize = MIN_TAIL_SIZE;
    snake->isInitialized = true;
}

void setSnakeDirection(snake_type *snake, const direction direction) {
    const bool invalidDirection =
            (direction != direction_left) && (direction != direction_right) &&
            (direction != direction_up) && (direction != direction_down);
    if (invalidDirection) {
        return;
    }
    const bool prohibitedDirection =
            ((snake->head.direction == direction_left) && (direction == direction_right)) ||
            ((snake->head.direction == direction_right) && (direction == direction_left)) ||
            ((snake->head.direction == direction_up) && (direction == direction_down)) ||
            ((snake->head.direction == direction_down) && (direction == direction_up));
    if (prohibitedDirection) {
        return;
    }
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
            snake->head.coords.y = clamp(++(snake->head.coords.y), minY, getmaxy(stdscr));
            break;
        default:
            break;
    }
}

bool isSnakeLooped(const snake_type *snake) {
    for (size_t i = 0UL; i < snake->tailSize; ++i) {
        if ((snake->head.coords.y == snake->tail[i].coords.y) &&
                (snake->head.coords.x == snake->tail[i].coords.x)) {
            return true;
        }
    }
    return false;
}

void drawSnake(const snake_type *snake) {
    for (size_t i = MAX_TAIL_SIZE; i > 0UL; --i) {
        mvprintw(snake->tail[i - 1UL].coords.y, snake->tail[i - 1UL].coords.x,
                "%c", snake->tail[i - 1UL].body.symbol);
    }

    mvprintw(snake->head.coords.y, snake->head.coords.x, "%c", snake->head.body.symbol);
}

void initWindow() {
    initscr(); //!< Инициализировать ncurses-окно.
    raw(); //!< Взять полный контроль над клавиатурой.
    noecho(); //!< Отключить отображение вводимых символов.
    keypad(stdscr, TRUE); //!< Включить функциональные клавиши.
    curs_set(FALSE); //!< Скрыть курсор.
    timeout(0); //!< Отключить блокировку терминала при вызове getch().
}

void closeWindow() {
    endwin(); //!< Завершить ncurses-режим.
}

bool isExitKey(const int key) {
    if (key == EXIT_KEY) {
        return true;
    }
    return false;
}

direction getDirectionByKey(const int key) {
    static const int keys[DIR_WAYS][DIR_KEYS] =
        {{KEY_LEFT, 'A', 'a'}, {KEY_RIGHT, 'D', 'd'}, {KEY_UP, 'W', 'w'}, {KEY_DOWN, 'S', 's'}};

    for (size_t way = 0UL; way < DIR_WAYS; ++way) {
        for (size_t button = 0UL; button < DIR_KEYS; ++button) {
            if (key == keys[way][button]) {
                return (direction) way;
            }
        }
    }

    return direction_unknown;
}

bool isGameWon(const snake_type *snake) {
    if (snake->tailSize == MAX_TAIL_SIZE) {
        return true;
    }
    return false;
}

bool isGameLost(const snake_type *snake) {
    return isSnakeLooped(snake);
}

state update(snake_type *snake) {
    const int pressedKey = getch();
    if (isExitKey(pressedKey)) {
        return state_exit;
    }

    setSnakeDirection(snake, getDirectionByKey(pressedKey));
    moveSnake(snake);

    if (isGameWon(snake)) {
        return state_won;
    }
    if (isGameLost(snake)) {
        return state_lost;
    }

    return state_process;
}

void draw(const snake_type *snake) {
    drawSnake(snake);
    refresh();
}
