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
 * @brief Названия месяцев.
 */
typedef enum {
    January = 1, //!< Январь.
    February, //!< Февраль.
    March, //!< Март.
    April, //!< Апрель.
    May, //!< Май.
    June, //!< Июнь.
    July, //!< Июль.
    August, //!< Август.
    September, //!< Сентябрь.
    October, //!< Октябрь.
    November, //!< Ноябрь.
    December //!< Декабрь.
} month;

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
 * @param[in] timestamp Временная метка.
 * @retval true - временная метка достоверна.
 * @retval false - временная метка недостоверна.
 */
bool isTimestampValid(const timestamp *timestamp);

/**
 * @brief Сформировать временную метку по формат-строке.
 * @details Если формат-строка пустая или содержит
 * недостоверные данные, то временная метка будет
 * сделана пустой.
 * @param[out] timestamp Временная метка.
 * @param[in] string Строка формата "ГГГГ.ММ.ДД-ЧЧ:ММ",
 * по которой будет сформирована временная метка.
 */
void makeTimestamp(timestamp *timestamp, const char *string);

/**
 * @brief Сделать временную метку пустой.
 * @param[out] timestamp Временная метка,
 * которую необходимо сделать пустой.
 */
void makeVoidTimestamp(timestamp *timestamp);

/**
 * @brief Определить, является ли временная метка пустой.
 * @param[in] timestamp Проверяемая временная метка.
 * @retval true - временная метка является пустой.
 * @retval false - временная метка не является пустой.
 */
bool isVoidTimestamp(const timestamp *timestamp);

/**
 * @brief Сравнить хронологически две временные метки.
 * @param[in] first Первая временная метка.
 * @param[in] second Вторая временная метка.
 * @retval Отрицательное число, если first < second.
 * @retval Нуль, если first = second.
 * @retval Положительное число, если first > second.
 */
int cmpTimestamps(const timestamp *first, const timestamp *second);

/**
 * @brief Проверить, входит ли метка sub во временную область, заданную меткой base.
 * @param[in] base Временная метка, определяющая временную область.
 * @param[in] sub Временная метка, вхождение которой необходимо проверить.
 * @retval true - метка sub входит во временную область метки base.
 * @retval false - метка sub не входит во временную область метки base.
 */
bool isSubTimestamp(const timestamp *base, const timestamp *sub);

/**
 * @brief Вывести в консоль временную метку.
 * @details Выводит только достоверные компоненты временной метки.
 * @param[in] timestamp Временная метка для вывода.
 */
void printTimestamp(const timestamp *timestamp);

/**
 * @}
 */
