#include "temperature.h"

/**
 * @brief Сравнить временные метки двух записей с датчика температуры.
 * @param first Первая запись с датчика температуры.
 * @param second Вторая запись с датчика температуры.
 * @retval Отрицательное число, если first < second.
 * @retval Нуль, если first = second.
 * @retval Положительное число, если first > second.
 */
static int cmpTempTimestamps(const void *first, const void *second) {
    const temp_data *f = *(const temp_data **)first;
    const temp_data *s = *(const temp_data **)second;
    return cmpTimestamps(&(f->timestamp), &(s->timestamp));
}

/**
 * @brief Сравнить значения двух записей с датчика температуры.
 * @param first Первая запись с датчика температуры.
 * @param second Вторая запись с датчика температуры.
 * @retval Отрицательное число, если first < second.
 * @retval Нуль, если first = second.
 * @retval Положительное число, если first > second.
 */
static int cmpTempRecords(const void *first, const void *second) {
    const temp_data *f = *(const temp_data **)first;
    const temp_data *s = *(const temp_data **)second;
    return (f->record.value - s->record.value);
}

void qsortTempByTimestamp(vector *records) {
    qsortVector(records, cmpTempTimestamps);
}

void qsortTempByRecord(vector *records) {
    qsortVector(records, cmpTempRecords);
}

temp_record getAverMonthTemp(const vector *records, const timestamp *timestamp) {
    temp_record result = {0, false};
    /**
     * @todo Добавить реализацию.
     */
    return result;
}

temp_record getMinMonthTemp(const vector *records, const timestamp *timestamp) {
    temp_record result = {0, false};
    /**
     * @todo Добавить реализацию.
     */
    return result;
}

temp_record getMaxMonthTemp(const vector *records, const timestamp *timestamp) {
    temp_record result = {0, false};
    /**
     * @todo Добавить реализацию.
     */
    return result;
}

temp_record getAverAnnualTemp(const vector *records, const timestamp *timestamp) {
    temp_record result = {0, false};
    /**
     * @todo Добавить реализацию.
     */
    return result;
}

temp_record getMinAnnualTemp(const vector *records, const timestamp *timestamp) {
    temp_record result = {0, false};
    /**
     * @todo Добавить реализацию.
     */
    return result;
}

temp_record getMaxAnnualTemp(const vector *records, const timestamp *timestamp) {
    temp_record result = {0, false};
    /**
     * @todo Добавить реализацию.
     */
    return result;
}
