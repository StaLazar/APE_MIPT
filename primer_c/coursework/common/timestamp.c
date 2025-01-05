#include "timestamp.h"

#include <time.h>

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
    static uint16_t year = MIN_YEAR;

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
    if ((MIN_YEAR <= timestamp->year) && (timestamp->year <= getCurrentYear())) {
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

void makeVoidTimestamp(timestamp *timestamp) {
    timestamp->year = VOID_YEAR;
    timestamp->month = VOID_MONTH;
    timestamp->day = VOID_DAY;
    timestamp->hour = VOID_HOUR;
    timestamp->minute = VOID_MINUTE;
}

bool isVoidTimestamp(const timestamp *timestamp) {
    return ((timestamp->year == VOID_YEAR) && (timestamp->month == VOID_MONTH) &&
            (timestamp->day == VOID_DAY) && (timestamp->hour == VOID_HOUR) &&
            (timestamp->minute == VOID_MINUTE));
}

int cmpTimestamps(const timestamp *first, const timestamp *second) {
    if (first->year != second->year) {
        return (int)(first->year) - (int)(second->year);
    }
    if (first->month != second->month) {
        return (int)(first->month) - (int)(second->month);
    }
    if (first->day != second->day) {
        return (int)(first->day) - (int)(second->day);
    }
    if (first->hour != second->hour) {
        return (int)(first->hour) - (int)(second->hour);
    }
    if (first->minute != second->minute) {
        return (int)(first->minute) - (int)(second->minute);
    }
    return 0;
}

bool isSubTimestamp(const timestamp *base, const timestamp *sub) {
    if (!isYearValid(base) || (base->year != sub->year)) {
        return false;
    }
    if (!isMonthValid(base)) {
        return true;
    }
    if (base->month != sub->month) {
        return false;
    }
    if (!isDayValid(base)) {
        return true;
    }
    if (base->day != sub->day) {
        return false;
    }
    if (!isHourValid(base)) {
        return true;
    }
    if (base->hour != sub->hour) {
        return false;
    }
    if (!isMinuteValid(base)) {
        return true;
    }
    if (base->minute != sub->minute) {
        return false;
    }
    return true;
}
