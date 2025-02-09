#pragma once

// #include "properties.h"

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Направление движения.
 */
typedef enum direction {
    direction_left = 0, //!< Влево.
    direction_right, //!< Вправо.
    direction_up, //!< Вверх.
    direction_down //!< Вниз.
} direction;

/**
 * @brief Пара чисел типа int.
 */
typedef struct pair_int {
    int x; //!< Первое число пары.
    int y; //!< Второе число пары.
} pair_int;

/**
 * @brief Тело змейки.
 * @details Представляет собой структуру,
 * определяющую данные для отрисовки тела.
 */
typedef struct snake_body {
    char symbol; //!< Символ-заполнитель.
} snake_body;

/**
 * @brief Голова змейки.
 */
typedef struct snake_head {
    pair_int coords; //!< Координаты.
    snake_body body; //!< Элемент для отрисовки.
    direction direction; //!< Направление движения.
} snake_head;

/**
 * @brief Хвост змейки.
 */
typedef struct snake_tail {
    pair_int coords; //!< Координаты.
    snake_body body; //!< Элемент для отрисовки.
} snake_tail;

/**
 * @brief Змейка.
 */
typedef struct snake {
    snake_head head; //!< Голова.
    snake_tail *tail; //!< Хвост.
    size_t tailSize; //!< Текущий размер хвоста.
    bool isInitialized; //!< Флаг инициализации.
} snake;

/**
 * @brief Инициализировать змейку.
 * @details В случае успешной инициализации змейки устанавливает
 * соответствующий флаг в true, а иначе - в false.
 * @param snake Змейка для инициализации.
 */
void initSnake(snake *snake);

/**
 * @brief Установить направление движения змейки.
 * @details Устанавливает направление движения головы змейки.
 * @param snake Змейка, направление движения которой необходимо установить.
 * @param direction Новое направление движения змейки.
 */
void setSnakeDirection(snake *snake, direction direction);

/**
 * @brief Переместить змейку.
 * @details Сдвигает голову змейки в направлении ее движения
 * и "подтягивает" вслед за ней весь хвост.
 * @param snake Змейка для перемещения.
 */
void moveSnake(snake *snake);

/**
 * @brief Отрисовать змейку.
 * @param snake Змейка для отрисовки.
 */
void drawSnake(const snake *snake);
