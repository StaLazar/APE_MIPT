#pragma once

#include "properties.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// ********************************************************************************* //
// ************************************* COMMON ************************************ //
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
 * @brief Данные для отрисовки.
 */
typedef struct draw_data {
    char symbol; //!< Символ-заполнитель.
} draw_data;

// ********************************************************************************* //
// ********************************* ЛОГИКА ЗМЕЙКИ ********************************* //
// ********************************************************************************* //

/**
 * @brief Голова змейки.
 */
typedef struct snake_head {
    pair_int coords; //!< Координаты.
    draw_data body; //!< Данные для отрисовки.
    direction direction; //!< Направление движения.
} snake_head;

/**
 * @brief Хвост змейки.
 */
typedef struct snake_tail {
    pair_int coords; //!< Координаты.
    draw_data body; //!< Данные для отрисовки.
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
 * @details Сдвигает голову змейки в направлении ее движения
 * и "подтягивает" вслед за ней весь хвост.
 * @param[out] snake Змейка для перемещения.
 */
void moveSnake(snake_type *snake);

/**
 * @brief Определить, врезалась ли в себя змейка.
 * @param[in] snake Змейка, состояние которой необходимо проверить.
 * @retval true Змейка врезалась в себя.
 * @retval false Змейка пребывает в нормальном состоянии.
 */
bool isSnakeLooped(const snake_type *snake);

/**
 * @brief Отрисовать змейку.
 * @param[in] snake Змейка для отрисовки.
 */
void drawSnake(const snake_type *snake);

// ********************************************************************************* //
// ********************************* ЛОГИКА ФРУКТОВ ******************************** //
// ********************************************************************************* //

/**
 * @brief Фрукт.
 */
typedef struct fruit_type {
    pair_int coords; //!< Координаты.
    draw_data body; //!< Данные для отрисовки.
    clock_t placementTime; //!< Время размещения на поле.
    bool isPlaced; //!< Флаг размещения на поле.
} fruit_type;

/**
 * @brief Тип массива фруктов.
 */
typedef fruit_type fruits_type[MAX_FRUITS_AMOUNT];

/**
 * @brief Инициализировать массив фруктов.
 * @param[out] fruits Массив фруктов для инициализации.
 */
void initFruits(fruits_type fruits);

/**
 * @brief Обновить состояния фруктов.
 * @param[out] fruits Массив фруктов для обновления.
 */
void updateFruits(fruits_type fruits);

/**
 * @brief Отрисовать массив фруктов.
 * @param[in] fruits Массив фруктов для отрисовки.
 */
void drawFruits(const fruits_type fruits);

// ********************************************************************************* //
// ******************************* ЛОГИКА ПРИЛОЖЕНИЯ ******************************* //
// ********************************************************************************* //

/**
 * @brief Состояние игры.
 */
typedef enum state {
    state_unknown = -1, //!< Неизвестно.
    state_process = 0, //!< В процессе.
    state_exit, //!< Прервана пользователем.
    state_won, //!< Завершена с победой.
    state_lost //!< Завершена с поражением.
} state;

/**
 * @brief Инициализировать окно приложения.
 */
void initWindow();

/**
 * @brief Закрыть окно приложения.
 */
void closeWindow();

/**
 * @brief Определить, является ли клавиша кнопкой завершения игры.
 * @param[in] key Численное значение, соответствующее нажатой клавише.
 * @retval true Клавиша является кнопкой завершения игры.
 * @retval false Клавиша не является кнопкой завершения игры.
 */
bool isExitKey(int key);

/**
 * @brief Получить направление движения по клавише.
 * @param[in] key Численное значение, соответствующее нажатой клавише.
 * @return Направление движения.
 */
direction getDirectionByKey(int key);

/**
 * @brief Определить, завершена ли игра с победой.
 * @details Игра считается завершенной с победой, если текущий размер
 * хвоста змейки совпал с максимальным.
 * @param[in] snake Змейка, по состоянию которой будет принято решение.
 * @retval true Игра завершена с победой.
 * @retval false Игра не завершена с победой.
 */
bool isGameWon(const snake_type *snake);

/**
 * @brief Определить, завершена ли игра с поражением.
 * @details Игра считается завершенной с поражением,
 * если змейка врезалась сама в себя.
 * @param[in] snake Змейка, по состоянию которой будет принято решение.
 * @retval true Игра завершена с поражением.
 * @retval false Игра не завершена с поражением.
 */
bool isGameLost(const snake_type *snake);

/**
 * @brief Проверить, какие фрукты были съедены змейкой.
 * Каждый съеденный фрукт пропадает с поля, при этом
 * хвост змейки увеличивается на единицу.
 * @param[out] snake Змейка, поедание фруктов которой будет проверено.
 * @param[out] fruits Массив фруктов для проверки.
 */
void checkEatenFruits(snake_type *snake, fruits_type fruits);

/**
 * @brief Выполнить одну итерацию обновления логики.
 * @param[out] snake Змейка, состояние которой будет обновлено.
 * @param[out] fruits Массив фруктов.
 * @return Состояние игры после одной итерации обновления логики.
 */
state update(snake_type *snake, fruits_type fruits);

/**
 * @brief Отрисовать границы игровой арены.
 */
void drawArena();

/**
 * @brief Отрисовать легенду игры.
 * @details Легенда игры состоит из следующих элементов:
 * прогресс, справка по управляющим клавишам.
 * @param[in] snake Змейка, определяющая прогресс игры.
 */
void drawLegend(const snake_type *snake);

/**
 * @brief Выполнить одну итерацию рисования.
 * @param[in] snake Змейка для отрисовки.
 * @param[in] fruits Массив фруктов для отрисовки.
 */
void draw(const snake_type *snake, const fruits_type fruits);

/**
 * @brief Вывести на экран результат игры.
 * @param[in] status Состояние игры.
 */
void drawResult(const state status);
