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

/**
 * @brief Найти участок массива данных с датчика температуры,
 * соответствующий заданной временной области.
 * @details Предполагается, что на вход подается отсортированный
 * по временной метке массив данных с датчика температуры.
 * Если искомый участок массива существует, то в
 * переменную begin будет записан индекс первого элемента
 * этого участка, а в end - индекс элемента, следующего за
 * последним элементом заданного участка.
 * @param records Массив данных с датчика температуры.
 * @param timestamp Указатель на временную метку, определяющую
 * заданную временную область.
 * @param begin Индекс начала искомого участка массива данных.
 * @param end Индекс конца искомого участка массива данных.
 */
static void findStatsLimits(const vector *records, const timestamp *timestamp,
        size_t *begin, size_t *end) {
    bool isBeginSet = false;
    for (size_t idx = 0; idx < getVectorSize(records); ++idx) {
        if (getVectorElement(records, idx) == NULL) {
            continue;
        }
        const temp_data *data = (const temp_data *) getVectorElement(records, idx);
        const bool isInTimeRange = isSubTimestamp(timestamp, &(data->timestamp));
        if (!isBeginSet && isInTimeRange) {
            *begin = idx;
            isBeginSet = true;
        }
        if (isBeginSet && !isInTimeRange) {
            *end = idx;
            return;
        }
    }
    if (isBeginSet && (*begin == (getVectorSize(records) - 1U))) {
        *end = *begin + 1U;
    }
}

bool readTempFromFile(const char *path, vector *records) {
    static const int valuesCount = 6;
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Incorrect path value");
        return false;
    }
    size_t lineNumber = 0;
    timestamp timeDate;
    temp_record record;
    int scanCount = EOF + 1;
    while (scanCount != EOF) {
        makeVoidTimestamp(&timeDate);
        makeTempRecord(&record, MAX_TEMPERATURE + 1);
        scanCount = fscanf(file, "%d;%d;%d;%d;%d;%d", &(timeDate.year), &(timeDate.month),
                &(timeDate.day), &(timeDate.hour), &(timeDate.minute), &(record.value));
        ++lineNumber;
        if (scanCount != valuesCount) {
            printf("Incorrect data format in line #%ld of file '%s'", lineNumber, path);
            continue;
        }
        makeTempRecord(&record, record.value);
        if (!isTimestampValid(&timeDate) || !record.isValid) {
            printf("Invalid data in line #%ld of file '%s'", lineNumber, path);
            continue;
        }
        temp_data data = {timeDate, record};
        addVectorElement(&records, &data);
    }
    fclose(file);
    return true;
}

void makeTempRecord(temp_record *record, const int8_t value) {
    record->value = value;
    if ((MIN_TEMPERATURE <= value) && (value <= MAX_TEMPERATURE)) {
        record->isValid = true;
    } else {
        record->isValid = false;
    }
}

void qsortTempByTimestamp(vector *records) {
    qsortVector(records, cmpTempTimestamps);
}

void qsortTempByRecord(vector *records) {
    qsortVector(records, cmpTempRecords);
}

void printTempStats(const vector *records, const timestamp *timestamp) {
    size_t begin = 0;
    size_t end = 0;
    findStatsLimits(records, timestamp, &begin, &end);
    if (begin == end) {
        printf("There is no data for the specified time period");
        return;
    }
    int8_t min = INT8_MAX;
    int8_t max = INT8_MIN;
    double average = 0.F;
    size_t validCount = 0U;
    for (size_t idx = begin; idx < end; ++idx) {
        if (getVectorElement(records, idx) == NULL) {
            continue;
        }
        const temp_data *data = (const temp_data *) getVectorElement(records, idx);
        if (!data->record.isValid) {
            continue;
        }
        ++validCount;
        min = (data->record.value < min) ? data->record.value : min;
        max = (data->record.value > max) ? data->record.value : max;
        average += (double)(data->record.value);
    }
    if (validCount == 0U) {
        printf("There is no valid data for the specified time period");
        return;
    }
    average /= validCount;
    printf("Minimum: %+d\tMaximum: %+d\tAverage: %+.3f", min, max, average);
}
