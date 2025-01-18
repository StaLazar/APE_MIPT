#include "timestamp.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//! Основание десятичной системы счисления.
#define BASE_10 10

/**
 * @brief Макрос обработки некорректной формат-строки временной метки.
 * @param[in] str Некорректная формат-строка для вывода в консоль.
 * @param[out] period Указатель на временную метку, которая будет сделана пустой.
 */
#define HANDLE_INVALID_FORMAT_STRING(str, period) \
    printf("Incorrect or invalid timestamp's format string: '%s'\n", (str)); \
    makeVoidTimestamp((period));

/**
 * @brief Макрос освобождения памяти с последующим вызовом return.
 * @param[out] ptr Указатель на объект, из-под которого нужно высвободить память.
 */
#define FREE_RETURN(ptr) \
    if ((ptr) != NULL) { \
        free((ptr)); \
        (ptr) = NULL; \
    } \
    return;

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
 * @param[in] year Год, подлежащий проверке.
 * @retval true Год является високосным.
 * @retval false Год не является високосным.
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
 * @param[in] timestamp Временная метка, год которой подлежит проверке.
 * @retval true Год временной метки достоверен.
 * @retval false Год временной метки недостоверен.
 */
static bool isYearValid(const timestamp *timestamp) {
    if ((MIN_YEAR <= timestamp->year) && (timestamp->year <= getCurrentYear())) {
        return true;
    }
    return false;
}

/**
 * @brief Определить достоверность месяца временной метки.
 * @param[in] timestamp Временная метка, месяц которой подлежит проверке.
 * @retval true Месяц временной метки достоверен.
 * @retval false Месяц временной метки недостоверен.
 */
static bool isMonthValid(const timestamp *timestamp) {
    if ((MIN_MONTH <= timestamp->month) && (timestamp->month <= MAX_MONTH)) {
        return true;
    }
    return false;
}

/**
 * @brief Определить достоверность дня временной метки.
 * @param[in] timestamp Временная метка, день которой подлежит проверке.
 * @retval true День временной метки достоверен.
 * @retval false День временной метки недостоверен.
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
 * @param[in] timestamp Временная метка, час которой подлежит проверке.
 * @retval true Час временной метки достоверен.
 * @retval false Час временной метки недостоверен.
 */
static bool isHourValid(const timestamp *timestamp) {
    if ((MIN_HOUR <= timestamp->hour) && (timestamp->hour <= MAX_HOUR)) {
        return true;
    }
    return false;
}

/**
 * @brief Определить достоверность минут временной метки.
 * @param[in] timestamp Временная метка, минуты которой подлежат проверке.
 * @retval true Минуты временной метки достоверны.
 * @retval false Минуты временной метки недостоверны.
 */
static bool isMinuteValid(const timestamp *timestamp) {
    if ((MIN_MINUTE <= timestamp->minute) && (timestamp->minute <= MAX_MINUTE)) {
        return true;
    }
    return false;
}

/**
 * @brief Извлечь из строки десятичное беззнаковое число.
 * @details В string будет записана строка, оставшаяся от исходной
 * после извлечения из нее искомого числа.
 * @param[in, out] string Строка, из которой будет извлечено число.
 * @param[in] marker Символ, предваряющий извлекаемое число.
 * @retval [0; LONG_MAX] Данные в строке корректны.
 * @retval -1 Данные в строке некорректны.
 */
static long getUnumFromStr(char *string, const char marker) {
    if ((strlen(string) == 0) || (string[0] != marker)) {
        return -1L;
    }
    for (size_t i = 0; i < strlen(string); ++i) {
        string[i] = string[i + 1];
    }
    if ((strlen(string) == 0) || (!isdigit(string[0]))) {
        return -1L;
    }
    char *remainder;
    const long int result = strtol(string, &remainder, BASE_10);
    strcpy(string, remainder);
    return result;
}

bool isTimestampValid(const timestamp *timestamp) {
    return (isYearValid(timestamp) && isMonthValid(timestamp) &&
            isDayValid(timestamp) && isHourValid(timestamp) &&
            isMinuteValid(timestamp));
}

void makeTimestamp(timestamp *timestamp, const char *string) {
    makeVoidTimestamp(timestamp);
    if (string == NULL) {
        return;
    }

    const size_t strSize = sizeof(char) * (strlen(string) + 5UL);
    char *str = (char *) malloc(strSize);
    if (str == NULL) {
        return;
    }
    memset(str, 0, strSize);
    strcat(str, "!");
    strcat(str, string);
    long number = -1L;

    number = getUnumFromStr(str, '!');
    timestamp->year = (number == -1L) ? VOID_YEAR : (uint16_t) number;
    if (!isYearValid(timestamp)) {
        HANDLE_INVALID_FORMAT_STRING(string, timestamp)
        FREE_RETURN(str)
    }
    if (strlen(str) == 0) {
        FREE_RETURN(str)
    }
    number = getUnumFromStr(str, '.');
    timestamp->month = (number == -1L) ? VOID_MONTH : (uint8_t) number;
    if (!isMonthValid(timestamp)) {
        HANDLE_INVALID_FORMAT_STRING(string, timestamp)
        FREE_RETURN(str)
    }
    if (strlen(str) == 0) {
        FREE_RETURN(str)
    }
    number = getUnumFromStr(str, '.');
    timestamp->day = (number == -1L) ? VOID_DAY : (uint8_t) number;
    if (!isDayValid(timestamp)) {
        HANDLE_INVALID_FORMAT_STRING(string, timestamp)
        FREE_RETURN(str)
    }
    if (strlen(str) == 0) {
        FREE_RETURN(str)
    }
    number = getUnumFromStr(str, '-');
    timestamp->hour = (number == -1L) ? VOID_HOUR : (uint8_t) number;
    if (!isHourValid(timestamp)) {
        HANDLE_INVALID_FORMAT_STRING(string, timestamp)
        FREE_RETURN(str)
    }
    if (strlen(str) == 0) {
        FREE_RETURN(str)
    }
    number = getUnumFromStr(str, ':');
    timestamp->minute = (number == -1L) ? VOID_MINUTE : (uint8_t) number;
    if ((!isMinuteValid(timestamp)) || (strlen(str) != 0)) {
        HANDLE_INVALID_FORMAT_STRING(string, timestamp)
        FREE_RETURN(str)
    }

    FREE_RETURN(str)
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

void printTimestamp(const timestamp *timestamp) {
    if (isTimestampValid(timestamp)) {
        printf("%04d.%02d.%02d-%02d:%02d", timestamp->year, timestamp->month,
                timestamp->day, timestamp->hour, timestamp->minute);
        return;
    }
    if (!isYearValid(timestamp)) {
        printf("UTST"); //!< Аббревиатура "Unknown timestamp".
        return;
    }
    printf("%04d", timestamp->year);
    if (!isMonthValid(timestamp)) {
        return;
    }
    printf(".%02d", timestamp->month);
    if (!isDayValid(timestamp)) {
        return;
    }
    printf(".%02d", timestamp->day);
    if (!isHourValid(timestamp)) {
        return;
    }
    printf("-%02d", timestamp->hour);
    if (!isMinuteValid(timestamp)) {
        return;
    }
    printf(":%02d", timestamp->minute);
}
