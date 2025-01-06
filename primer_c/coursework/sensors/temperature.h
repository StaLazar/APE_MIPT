#pragma once

#include "common/timestamp.h"
#include "common/vector.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup sensors
 * @{
 */

//! Минимальное значение температуры.
#define MIN_TEMPERATURE -99
//! Максимальное значение температуры.
#define MAX_TEMPERATURE 99

/**
 * @brief Значение температуры с достоверностью.
 */
typedef struct {
    int8_t value; //!< Значение.
    bool isValid; //!< Достоверность.
} temp_record;

/**
 * @brief Данные с датчика температуры.
 */
typedef struct {
    timestamp timestamp; //!< Временная метка.
    temp_record record; //!< Значение.
} temp_data;

/**
 * @brief Получить значение температуры с достоверностью.
 * @param value Значение температуры.
 * @retval Достоверное значение, если переданная температура
 * лежит в допустимом диапазоне.
 * @retval Недостоверное значение, если переданная температура
 * выходит за допустимый диапазон.
 */
temp_record makeTempRecord(int8_t value);

/**
 * @brief Отсортировать массив данных с датчика
 * температуры по временной метке.
 * @param records Массив данных с датчика температуры.
 */
void qsortTempByTimestamp(vector *records);

/**
 * @brief Отсортировать массив данных с датчика
 * температуры по значению температуры.
 * @param records Массив данных с датчика температуры.
 */
void qsortTempByRecord(vector *records);

/**
 * @brief Вывести статистику по температуре за указанный временной период.
 * @param records Массив данных с датчика температуры.
 * @param timestamp Указатель на временную метку, определяющую временной
 * период, за который необходимо вывести статистику.
 */
void printTimeTempStats(const vector *records, const timestamp *timestamp);

/**
 * @}
 */
