#include "logic.h"

#include <stdlib.h>
#include <string.h>
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

    switch (snake->head.direction) {
        case direction_left:
            snake->head.coords.x =
                    clamp(--(snake->head.coords.x), ARENA_MIN_COORD_X, ARENA_MAX_COORD_X);
            break;
        case direction_right:
            snake->head.coords.x =
                    clamp(++(snake->head.coords.x), ARENA_MIN_COORD_X, ARENA_MAX_COORD_X);
            break;
        case direction_up:
            snake->head.coords.y =
                    clamp(--(snake->head.coords.y), ARENA_MIN_COORD_Y, ARENA_MAX_COORD_Y);
            break;
        case direction_down:
            snake->head.coords.y =
                    clamp(++(snake->head.coords.y), ARENA_MIN_COORD_Y, ARENA_MAX_COORD_Y);
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

void initFruits(fruits_type fruits) {
    for (size_t i = 0UL; i < MAX_FRUITS_AMOUNT; ++i) {
        fruits[i].coords.y = ARENA_MIN_COORD_Y + 1;
        fruits[i].coords.x = ARENA_MIN_COORD_X + 1;
        fruits[i].body.symbol = BODY_IDLE;
        fruits[i].placementTime = 0L;
        fruits[i].isPlaced = false;
    }
}

void updateFruits(fruits_type fruits) {
    const clock_t now = clock();
    for (size_t i = 0UL; i < MAX_FRUITS_AMOUNT; ++i) {
        if (fruits[i].isPlaced) {
            const float duration = ((float)(now - fruits[i].placementTime) / CLOCKS_PER_SEC);
            if (duration > FRUIT_LIFE_TIMEOUT_SEC) {
                fruits[i].body.symbol = BODY_IDLE;
                fruits[i].isPlaced = false;
            }
        } else {
            fruits[i].coords.y = (ARENA_MIN_COORD_Y + 1) +
                    (rand() % (ARENA_MAX_COORD_Y - ARENA_MIN_COORD_Y - 1));
            fruits[i].coords.x = (ARENA_MIN_COORD_X + 1) +
                    (rand() % (ARENA_MAX_COORD_X - ARENA_MIN_COORD_X - 1));
            fruits[i].body.symbol = BODY_FRUIT;
            fruits[i].placementTime = now;
            fruits[i].isPlaced = true;
        }
    }
}

void drawFruits(const fruits_type fruits) {
    for (size_t i = 0UL; i < MAX_FRUITS_AMOUNT; ++i) {
        mvprintw(fruits[i].coords.y, fruits[i].coords.x, "%c", fruits[i].body.symbol);
    }
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

void checkEatenFruits(snake_type *snake, fruits_type fruits) {
    for (size_t i = 0UL; i < MAX_FRUITS_AMOUNT; ++i) {
        if (fruits[i].isPlaced && (fruits[i].coords.y == snake->head.coords.y) &&
                (fruits[i].coords.x == snake->head.coords.x)) {
            fruits[i].body.symbol = BODY_IDLE;
            fruits[i].isPlaced = false;
            snake->tail[snake->tailSize++].body.symbol = BODY_TAIL;
        }
    }
}

state update(snake_type *snake, fruits_type fruits) {
    const int pressedKey = getch();
    if (isExitKey(pressedKey)) {
        return state_exit;
    }

    setSnakeDirection(snake, getDirectionByKey(pressedKey));
    moveSnake(snake);
    updateFruits(fruits);
    checkEatenFruits(snake, fruits);

    if (isGameWon(snake)) {
        return state_won;
    }
    if (isGameLost(snake)) {
        return state_lost;
    }

    return state_process;
}

void drawArena() {
    move(ARENA_MIN_COORD_Y, ARENA_MIN_COORD_X);
    hline(ACS_HLINE, ARENA_MAX_COORD_X - ARENA_MIN_COORD_X);
    vline(ACS_VLINE, ARENA_MAX_COORD_Y - ARENA_MIN_COORD_Y);
    addch(ACS_ULCORNER);
    move(ARENA_MIN_COORD_Y, ARENA_MAX_COORD_X);
    vline(ACS_VLINE, ARENA_MAX_COORD_Y - ARENA_MIN_COORD_Y);
    addch(ACS_URCORNER);
    move(ARENA_MAX_COORD_Y, ARENA_MIN_COORD_X);
    hline(ACS_HLINE, ARENA_MAX_COORD_X - ARENA_MIN_COORD_X);
    addch(ACS_LLCORNER);
    move(ARENA_MAX_COORD_Y, ARENA_MAX_COORD_X);
    addch(ACS_LRCORNER);
}

void drawLegend(const snake_type *snake) {
    static const char *manStr = "WASD, ARROWS - Control. F10 - Exit.";
    const int manCoordY = getmaxy(stdscr) - (ARENA_OFFSET_Y / 2);
    const int manCoordX = (getmaxx(stdscr) / 2) - (strlen(manStr) / 2);

    static const char *progressStr = "Current tail size: %d/%d. Eat %d fruit(s) to win.";
    const int progressCoordY = getbegy(stdscr) + (ARENA_OFFSET_Y / 2);
    const int progressCoordX = (getmaxx(stdscr) / 2) - (strlen(progressStr) / 2);

    mvprintw(manCoordY, manCoordX, "%s", manStr);
    mvprintw(progressCoordY, progressCoordX, progressStr,
            snake->tailSize, MAX_TAIL_SIZE, MAX_TAIL_SIZE - snake->tailSize);
}

void draw(const snake_type *snake, const fruits_type fruits) {
    drawFruits(fruits);
    drawSnake(snake);
    drawArena();
    drawLegend(snake);
    refresh();
}
