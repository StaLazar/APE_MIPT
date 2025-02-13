#pragma once

#include "properties.h"

#include <stdio.h>
#include <stdbool.h>

// ********************************************************************************* //
// ********************************* ЛОГИКА ЗМЕЙКИ ********************************* //
// ********************************************************************************* //

/**
 * @brief Направление движения.
 */
typedef enum direction {
    direction_unknown = -1, //!< Неизвестно.
    direction_left = 0, //!< Влево.
    direction_right, //!< Вправо.
    direction_up, //!< Вверх.
    direction_down //!< Вниз.
} direction;

/**
 * @brief Пара чисел типа int.
 */
typedef struct pair_int {
    int y; //!< Первое число пары.
    int x; //!< Второе число пары.
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
typedef struct snake_type {
    snake_head head; //!< Голова.
    snake_tail tail[MAX_TAIL_SIZE]; //!< Хвост.
    size_t tailSize; //!< Текущий размер хвоста.
    bool isInitialized; //!< Флаг инициализации.
} snake_type;

/**
 * @brief Инициализировать змейку.
 * @details В случае успешной инициализации змейки устанавливает
 * соответствующий флаг в true, а иначе - в false.
 * @param[out] snake Змейка для инициализации.
 */
void initSnake(snake_type *snake);

/**
 * @brief Установить направление движения змейки.
 * @details Устанавливает направление движения головы змейки,
 * только если оно имеет допустимое значение.
 * @param[out] snake Змейка, направление движения которой необходимо установить.
 * @param[in] direction Новое направление движения змейки.
 */
void setSnakeDirection(snake_type *snake, direction direction);

/**
 * @brief Переместить змейку.
 * @todo Добавить возврат флага о том, что змейка врезалась в себя же?
 * Или не возврат флага, а изменение переменной, переданной через указатель.
 * @details Сдвигает голову змейки в направлении ее движения
 * и "подтягивает" вслед за ней весь хвост.
 * @param[out] snake Змейка для перемещения.
 */
void moveSnake(snake_type *snake);

/**
 * @brief Отрисовать змейку.
 * @param[in] snake Змейка для отрисовки.
 */
void drawSnake(const snake_type *snake);

// ********************************************************************************* //
// ******************************* ЛОГИКА ПРИЛОЖЕНИЯ ******************************* //
// ********************************************************************************* //

/**
 * @brief Инициализировать окно приложения.
 */
void initWindow();

/**
 * @brief Закрыть окно приложения.
 */
void closeWindow();

/**
 * @brief Получить направление движения по клавише.
 * @param key Численное значение, соответствующее нажатой клавише.
 * @return Направление движения.
 */
direction getDirectionByKey(int key);

/**
 * @brief Выполнить одну итерацию обновления логики.
 * @param snake Змейка, состояние которой будет обновлено.
 */
void update(snake_type *snake);

/**
 * @brief Выполнить одну итерацию рисования.
 * @param snake Змейка для отрисовки.
 */
void draw(const snake_type *snake);
