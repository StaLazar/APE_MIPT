#include "timestamp.h"

#include <time.h>

//! Год, с которого начинается отсчет лет.
#define BASE_YEAR 1900U
//! Минимальный номер месяца.
#define MIN_MONTH 1U
//! Максимальный номер месяца.
#define MAX_MONTH 12U
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
//! Минимальное число часов.
#define MIN_HOUR 0U
//! Максимальное число часов.
#define MAX_HOUR 23U
//! Минимальное число минут.
#define MIN_MINUTE 0U
//! Максимальное число минут.
#define MAX_MINUTE 59U

/**
 * @brief Названия месяцев.
 */
enum {
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
};

/**
 * @brief Получить текущий год.
 * @return Текущий год.
 */
static uint16_t getCurrentYear() {
    static bool isInitialized = false;
    static uint16_t year = BASE_YEAR;

    if (!isInitialized) {
        time_t timer = time(NULL);
        struct tm *curTime = localtime(&timer);
        year += (uint16_t)curTime->tm_year;
        isInitialized = true;
    }

    return year;
}

/**
 * @brief Определить, является ли год високосным.
 * @param year Год, подлежащий проверке.
 * @retval true - год является високосным.
 * @retval false - год не является високосным.
 */
static bool isLeapYear(const uint16_t year) {
    if (year % 400U == 0U) {
        return true;
    }
    if (year % 100U == 0U) {
        return false;
    }
    if (year % 4U == 0U) {
        return true;
    }
    return false;
}

/**
 * @brief Определить достоверность года временной метки.
 * @param timestamp Временная метка, год которой подлежит проверке.
 * @retval true - год временной метки достоверен.
 * @retval false - год временной метки недостоверен.
 */
static bool isYearValid(const timestamp *timestamp) {
    if ((BASE_YEAR <= timestamp->year) && (timestamp->year <= getCurrentYear())) {
        return true;
    }
    return false;
}

/**
 * @brief Определить достоверность месяца временной метки.
 * @param timestamp Временная метка, месяц которой подлежит проверке.
 * @retval true - месяц временной метки достоверен.
 * @retval false - месяц временной метки недостоверен.
 */
static bool isMonthValid(const timestamp *timestamp) {
    if ((MIN_MONTH <= timestamp->month) && (timestamp->month <= MAX_MONTH)) {
        return true;
    }
    return false;
}

/**
 * @brief Определить достоверность дня временной метки.
 * @param timestamp Временная метка, день которой подлежит проверке.
 * @retval true - день временной метки достоверен.
 * @retval false - день временной метки недостоверен.
 */
static bool isDayValid(const timestamp *timestamp) {
    switch (timestamp->month) {
        case February:
            const uint16_t maxDay = isLeapYear(timestamp->year) ? MAX_DAY_29 : MAX_DAY_28;
            return ((MIN_DAY <= timestamp->day) && (timestamp->day <= maxDay)) ? true : false;
        case April:
        case June:
        case September:
        case November:
            return ((MIN_DAY <= timestamp->day) && (timestamp->day <= MAX_DAY_30)) ? true : false;
        case January:
        case March:
        case May:
        case July:
        case August:
        case October:
        case December:
            return ((MIN_DAY <= timestamp->day) && (timestamp->day <= MAX_DAY_31)) ? true : false;
    }
    return false;
}

/**
 * @brief Определить достоверность часа временной метки.
 * @param timestamp Временная метка, час которой подлежит проверке.
 * @retval true - час временной метки достоверен.
 * @retval false - час временной метки недостоверен.
 */
static bool isHourValid(const timestamp *timestamp) {
    if ((MIN_HOUR <= timestamp->hour) && (timestamp->hour <= MAX_HOUR)) {
        return true;
    }
    return false;
}

/**
 * @brief Определить достоверность минут временной метки.
 * @param timestamp Временная метка, минуты которой подлежат проверке.
 * @retval true - минуты временной метки достоверны.
 * @retval false - минуты временной метки недостоверны.
 */
static bool isMinuteValid(const timestamp *timestamp) {
    if ((MIN_MINUTE <= timestamp->minute) && (timestamp->minute <= MAX_MINUTE)) {
        return true;
    }
    return false;
}

bool isTimestampValid(const timestamp *timestamp) {
    return (isYearValid(timestamp) && isMonthValid(timestamp) &&
            isDayValid(timestamp) && isHourValid(timestamp) &&
            isMinuteValid(timestamp));
}

int cmpTimestamps(const timestamp *first, const timestamp *second) {
    if (first->year != second->year) {
        return (int)(first->year - second->year);
    }
    if (first->month != second->month) {
        return (int)(first->month - second->month);
    }
    if (first->day != second->day) {
        return (int)(first->day - second->day);
    }
    if (first->hour != second->hour) {
        return (int)(first->hour - second->hour);
    }
    if (first->minute != second->minute) {
        return (int)(first->minute - second->minute);
    }
    return 0;
}
