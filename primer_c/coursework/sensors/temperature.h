#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "common/timestamp.h"

/**
 * @ingroup sensors
 * @brief Значение температуры с достоверностью.
 */
typedef struct {
    int8_t value; //!< Значение.
    bool isValid; //!< Достоверность.
} temp_record;

/**
 * @ingroup sensors
 * @brief Данные с датчика температуры.
 */
typedef struct {
    timestamp timestamp; //!< Временная метка.
    temp_record record; //!< Значение.
} temp_data;

/**
 * @ingroup sensors
 * @brief Получить значение среднемесячной температуры.
 * @param records Массив данных с датчика температуры.
 * @param size Размер массива данных с датчика температуры.
 * @param timestamp Временная метка, год и месяц которой определяют
 * область поиска значения среднемесячной температуры.
 * @return Достоверное значение температуры, если в массиве данных есть
 * хотя бы одна запись в указанной временной области, а иначе - недостоверное.
 */
temp_record getAverMonthTemp(const temp_data *records, size_t size, timestamp timestamp);

/**
 * @ingroup sensors
 * @brief Получить значение минимальной месячной температуры.
 * @param records Массив данных с датчика температуры.
 * @param size Размер массива данных с датчика температуры.
 * @param timestamp Временная метка, год и месяц которой определяют
 * область поиска значения минимальной месячной температуры.
 * @return Достоверное значение температуры, если в массиве данных есть
 * хотя бы одна запись в указанной временной области, а иначе - недостоверное.
 */
temp_record getMinMonthTemp(const temp_data *records, size_t size, timestamp timestamp);

/**
 * @ingroup sensors
 * @brief Получить значение максимальной месячной температуры.
 * @param records Массив данных с датчика температуры.
 * @param size Размер массива данных с датчика температуры.
 * @param timestamp Временная метка, год и месяц которой определяют
 * область поиска значения максимальной месячной температуры.
 * @return Достоверное значение температуры, если в массиве данных есть
 * хотя бы одна запись в указанной временной области, а иначе - недостоверное.
 */
temp_record getMaxMonthTemp(const temp_data *records, size_t size, timestamp timestamp);

/**
 * @ingroup sensors
 * @brief Получить значение среднегодовой температуры.
 * @param records Массив данных с датчика температуры.
 * @param size Размер массива данных с датчика температуры.
 * @param timestamp Временная метка, год которой определяет
 * область поиска значения среднегодовой температуры.
 * @return Достоверное значение температуры, если в массиве данных есть
 * хотя бы одна запись в указанной временной области, а иначе - недостоверное.
 */
temp_record getAverAnnualTemp(const temp_data *records, size_t size, timestamp timestamp);

/**
 * @ingroup sensors
 * @brief Получить значение минимальной годовой температуры.
 * @param records Массив данных с датчика температуры.
 * @param size Размер массива данных с датчика температуры.
 * @param timestamp Временная метка, год которой определяет
 * область поиска значения минимальной годовой температуры.
 * @return Достоверное значение температуры, если в массиве данных есть
 * хотя бы одна запись в указанной временной области, а иначе - недостоверное.
 */
temp_record getMinAnnualTemp(const temp_data *records, size_t size, timestamp timestamp);

/**
 * @ingroup sensors
 * @brief Получить значение максимальной годовой температуры.
 * @param records Массив данных с датчика температуры.
 * @param size Размер массива данных с датчика температуры.
 * @param timestamp Временная метка, год которой определяет
 * область поиска значения максимальной годовой температуры.
 * @return Достоверное значение максимальной годовой температуры, если в массиве данных
 * есть хотя бы одна запись в указанной временной области, а иначе - недостоверное.
 */
temp_record getMaxAnnualTemp(const temp_data *records, size_t size, timestamp timestamp);
