#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup common
 * @{
 */

//! Минимальный номер года.
#define MIN_YEAR 1900U
//! Незаданный номер года.
#define VOID_YEAR (MIN_YEAR - 1U)
//! Минимальный номер месяца.
#define MIN_MONTH 1U
//! Максимальный номер месяца.
#define MAX_MONTH 12U
//! Незаданный номер месяца.
#define VOID_MONTH (MAX_MONTH + 1U)
//! Минимальный номер дня.
#define MIN_DAY 1U
//! Максимальный номер дня во 2 месяце невисокосного года.
#define MAX_DAY_28 28U
//! Максимальный номер дня во 2 месяце високосного года.
#define MAX_DAY_29 29U
//! Максимальный номер дня в 4, 6, 9, 11 месяцах.
#define MAX_DAY_30 30U
//! Максимальный номер дня в 1, 3, 5, 7, 8, 10, 12 месяцах.
#define MAX_DAY_31 31U
//! Незаданный номер дня.
#define VOID_DAY (MAX_DAY_31 + 1U)
//! Минимальное число часов.
#define MIN_HOUR 0U
//! Максимальное число часов.
#define MAX_HOUR 23U
//! Незаданное число часов.
#define VOID_HOUR (MAX_HOUR + 1U)
//! Минимальное число минут.
#define MIN_MINUTE 0U
//! Максимальное число минут.
#define MAX_MINUTE 59U
//! Незаданное число минут.
#define VOID_MINUTE (MAX_MINUTE + 1U)

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
 * @retval true - временная метка достоверна.
 * @retval false - временная метка недостоверна.
 */
bool isTimestampValid(const timestamp *timestamp);

/**
 * @brief Сделать временную метку пустой.
 * @param timestamp Указатель на временную метку,
 * которую необходимо сделать пустой.
 */
void makeVoidTimestamp(timestamp *timestamp);

/**
 * @brief Определить, является ли временная метка пустой.
 * @param timestamp Указатель на проверяемую временную метку.
 * @retval true - временная метка является пустой.
 * @retval false - временная метка не является пустой.
 */
bool isVoidTimestamp(const timestamp *timestamp);

/**
 * @brief Сравнить хронологически две временные метки.
 * @param first Первая временная метка.
 * @param second Вторая временная метка.
 * @retval Отрицательное число, если first < second.
 * @retval Нуль, если first = second.
 * @retval Положительное число, если first > second.
 */
int cmpTimestamps(const timestamp *first, const timestamp *second);

/**
 * @brief Проверить, входит ли метка sub во временную область, заданную меткой base.
 * @param base Указатель на временную метку, определяющую временную область.
 * @param sub Указатель на временную метку, вхождение которой необходимо проверить.
 * @retval true - метка sub входит во временную область метки base.
 * @retval false - метка sub не входит во временную область метки base.
 */
bool isSubTimestamp(const timestamp *base, const timestamp *sub);

/**
 * @}
 */
