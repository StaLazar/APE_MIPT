#pragma once

#include "timestamp.h"
#include "vector.h"

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
 * @brief Прочитать из файла данные с датчика температуры
 * в соответствии с протоколом информационного взаимодействия.
 * @details При обнаружении данных, отличных от протокола,
 * выводит в консоль сообщение с указанием строки файла,
 * в которой содержится некорректная информация.
 * @param[in] path Путь до файла с данными.
 * @param[out] records Массив данных, который будет заполнен
 * информацией из переданного файла.
 * @retval true Чтение данных прошло успешно.
 * @retval false Чтение данных завершилось ошибкой.
 */
bool readTempFromFile(const char *path, vector *records);

/**
 * @brief Сформировать значение температуры с достоверностью.
 * @details Если value лежит в допустимом диапазоне температур,
 * то в record будет записано достоверное значение, а иначе -
 * недостоверное.
 * @param[out] record Формируемое значение температуры с достоверностью.
 * @param[in] value Значение температуры.
 */
void makeTempRecord(temp_record *record, int8_t value);

/**
 * @brief Отсортировать массив данных с датчика
 * температуры по временной метке.
 * @param[out] records Массив данных с датчика температуры.
 */
void qsortTempByTimestamp(vector *records);

/**
 * @brief Отсортировать массив данных с датчика
 * температуры по значению температуры.
 * @param[out] records Массив данных с датчика температуры.
 */
void qsortTempByRecord(vector *records);

/**
 * @brief Вывести в консоль значение температуры с достоверностью.
 * @param[in] record Значение температуры с достоверностью для вывода.
 */
void printTempRecord(const temp_record *record);

/**
 * @brief Вывести в консоль статистику по температуре
 * за указанный временной период.
 * @details Предполагается, что на вход подается отсортированный
 * по временной метке массив данных с датчика температуры.
 * Если данные по температуре за указанный временной
 * период отсутствуют или недостоверны, то выведет в консоль
 * соответствующее сообщение, а иначе - статистику в формате
 * "Timestamp: XXXX.XX.XX-XX:XX | Minimum: XX | Maximum: XX | Average: XX.XXX".
 * @param[in] records Массив данных с датчика температуры.
 * @param[in] timestamp Временная метка, определяющая
 * временной период, за который необходимо вывести статистику.
 */
void printPeriodTempStats(const vector *records, const timestamp *timestamp);

/**
 * @brief Вывести в консоль статистику по температуре
 * за указанные в массиве данных годы и месяцы.
 * @details Предполагается, что на вход подается отсортированный
 * по временной метке массив данных с датчика температуры.
 * Если данные по температуре за какой-либо год или месяц отсутствуют
 * или недостоверны, то выведет в консоль соответствующее сообщение,
 * а иначе - статистику вида "Год -> Месяцы" в формате
 * "Timestamp: XXXX.XX.XX-XX:XX | Minimum: XX | Maximum: XX | Average: XX.XXX".
 * @param[in] records Массив данных с датчика температуры.
 */
void printGlobalTempStats(const vector *records);

/**
 * @}
 */
