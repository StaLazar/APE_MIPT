#pragma once

#include "common.h"

/**
 * @brief Получить абсциссу пересечения графиков функций first и second.
 * @details Для определения абсциссы пересечения графиков используется
 * метод хорд.
 * @param scope Окрестность абсциссы пересечения графиков функций.
 * @param first Математическая функция одной переменной.
 * @param second Математическая функция одной переменной.
 * @param precision Точность вычислений.
 * @return Искомая абсцисса.
 */
float getRoot(float_pair scope, function *first, function *second, float precision);

/**
 * @brief Получить площадь фигуры, ограниченной графиками функций upper и lower и
 * двумя вертикальными прямыми на отрезке, указанном в scope.
 * @details Определение площади производится с помощью интеграла,
 * вычисленного методом трапеции.
 * @param scope Отрезок интегрирования.
 * @param upper Математическая функция одной переменной, график которой
 * определяет "верхний контур" фигуры.
 * @param lower Математическая функция одной переменной, график которой
 * определяет "нижний контур" фигуры.
 * @param precision Точность вычислений.
 * @return Искомая площадь.
 */
float getSquare(float_pair scope, function *upper, function *lower, float precision);
