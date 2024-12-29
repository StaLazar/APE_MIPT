#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
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
 * @brief Определить достоверность временной метки.
 * @param timestamp Временная метка.
 * @return true - временная метка достоверна, false - иначе.
 */
bool isTimestampValid(const timestamp *timestamp);
