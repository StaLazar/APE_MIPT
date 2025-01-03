#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup common
 * @brief Временная метка.
 */
typedef struct {
    uint16_t year; //!< Год.
    uint8_t month; //!< Месяц.
    uint8_t day; //!< День.
    uint8_t hour; //!< Час.
    uint8_t minute; //!< Минута.
} timestamp;

/**
 * @ingroup common
 * @brief Определить достоверность временной метки.
 * @param timestamp Временная метка.
 * @retval true - временная метка достоверна.
 * @retval false - временная метка недостоверна.
 */
bool isTimestampValid(const timestamp *timestamp);

/**
 * @ingroup common
 * @brief Сравнить хронологически две временные метки.
 * @param first Первая временная метка.
 * @param second Вторая временная метка.
 * @retval Отрицательное число, если first < second.
 * @retval Нуль, если first = second.
 * @retval Положительное число, если first > second.
 */
int cmpTimestamps(const timestamp *first, const timestamp *second);
