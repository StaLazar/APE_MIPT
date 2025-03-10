#pragma once

//! Число точек пересечения функций f(x), g(x), h(x).
#define ROOTS_COUNT 5UL

/**
 * @brief Пара чисел типа float.
 */
typedef struct float_pair {
    float first; //!< Первое число пары.
    float second; //!< Второе число пары.
} float_pair;

//! Окрестности абсцисс пересечения графиков функций f(x), g(x), h(x).
extern float_pair rootScopes[ROOTS_COUNT];

//! Абсциссы пересечения графиков функций f(x), g(x), h(x).
extern float roots[ROOTS_COUNT];

/**
 * @brief Тип математической функции одной переменной.
 */
typedef float (function)(float x);

/**
 * @brief Получить разницу функций first и second в точке x.
 * @param[in] first Математическая функция одной переменной.
 * @param[in] second Математическая функция одной переменной.
 * @param[in] x Аргумент функции.
 * @return Искомая разница.
 */
float getDifference(function *first, function *second, float x);

/**
 * @brief Линейная функция f(x).
 * @param[in] x Аргумент функции.
 * @return Значение функции f(x).
 */
float f(const float x);

/**
 * @brief Кубическая функция g(x).
 * @param[in] x Аргумент функции.
 * @return Значение функции g(x).
 */
float g(const float x);

/**
 * @brief Обратная пропорциональность h(x).
 * @attention Деление на 0 недопустимо.
 * @param[in] x Аргумент функции.
 * @return Значение функции h(x), если x != 0,
 * иначе - 0.
 */
float h(const float x);
