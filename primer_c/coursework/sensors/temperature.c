#include "temperature.h"

/**
 * @brief Макрос вывода временной метки в консоль в формате
 * "Timestamp: XXXX.XX.XX-XX:XX | ".
 * @param[in] period Указатель на временную метку для вывода в консоль.
 */
#define PRINT_TIMESTAMP(period) \
    printf("Timestamp: "); \
    printTimestamp((period)); \
    printf(" | ");

/**
 * @brief Сравнить временные метки двух записей с датчика температуры.
 * @param[in] first Первая запись с датчика температуры.
 * @param[in] second Вторая запись с датчика температуры.
 * @retval < 0 Если first < second.
 * @retval 0 Если first = second.
 * @retval > 0 Если first > second.
 */
static int cmpTempTimestamps(const void *first, const void *second) {
    const temp_data *f = *(const temp_data **)first;
    const temp_data *s = *(const temp_data **)second;
    return cmpTimestamps(&(f->timestamp), &(s->timestamp));
}

/**
 * @brief Сравнить значения двух записей с датчика температуры.
 * @param[in] first Первая запись с датчика температуры.
 * @param[in] second Вторая запись с датчика температуры.
 * @retval < 0 Если first < second.
 * @retval 0 Если first = second.
 * @retval > 0 Если first > second.
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
 * @param[in] records Массив данных с датчика температуры.
 * @param[in] timestamp Временная метка, определяющая
 * заданную временную область.
 * @param[out] begin Индекс начала искомого участка массива данных.
 * @param[out] end Индекс конца искомого участка массива данных.
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
    if (isBeginSet) {
        *end = getVectorSize(records);
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
    timestamp period;
    temp_record record;
    int scanCount = 0;
    while (true) {
        makeVoidTimestamp(&period);
        makeTempRecord(&record, MAX_TEMPERATURE + 1);
        scanCount = fscanf(file, "%hd;%hhd;%hhd;%hhd;%hhd;%hhd",
                &(period.year), &(period.month), &(period.day),
                &(period.hour), &(period.minute), &(record.value));
        ++lineNumber;
        if (scanCount == EOF) {
            break;
        } else if (scanCount != valuesCount) {
            printf("Incorrect data format in line #%ld of file '%s'\n", lineNumber, path);
            //! Очистка буфера от некорректных данных:
            fscanf(file, "%*[^\n]");
            fscanf(file, "%*c");
            continue;
        }
        makeTempRecord(&record, record.value);
        if (!isTimestampValid(&period) || !record.isValid) {
            printf("Invalid data in line #%ld of file '%s'\n", lineNumber, path);
            continue;
        }
        temp_data data = {period, record};
        addVectorElement(records, &data);
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

void printTempRecord(const temp_record *record) {
    printf("%+02d (%d)", record->value, record->isValid);
}

void printPeriodTempStats(const vector *records, const timestamp *timestamp) {
    if (isVectorEmpty(records)) {
        printf("There is no data for statistics' output\n");
        return;
    }
    size_t begin = 0;
    size_t end = 0;
    findStatsLimits(records, timestamp, &begin, &end);
    if (begin == end) {
        PRINT_TIMESTAMP(timestamp)
         //! Аббревиатура "No suitable data":
        printf("Minimum: NSD | Maximum: NSD | Average:   NSD\n");
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
        PRINT_TIMESTAMP(timestamp)
         //! Аббревиатура "No valid data":
        printf("Minimum: NVD | Maximum: NVD | Average:   NVD\n");
        return;
    }
    average /= validCount;
    PRINT_TIMESTAMP(timestamp)
    printf("Minimum: %+03hhd | Maximum: %+03hhd | Average: %+07.3f\n", min, max, average);
}

void printGlobalTempStats(const vector *records) {
    if (isVectorEmpty(records)) {
        printf("There is no data for statistics' output\n");
        return;
    }
    const temp_data *firstRecord = (const temp_data *) getVectorElement(records, 0UL);
    const temp_data *lastRecord =
            (const temp_data *) getVectorElement(records, getVectorSize(records) - 1UL);
    const uint16_t firstYear = firstRecord->timestamp.year;
    const uint16_t lastYear = lastRecord->timestamp.year;
    for (uint16_t year = firstYear; year <= lastYear; ++year) {
        timestamp period;
        makeVoidTimestamp(&period);
        period.year = year;
        printf("   ");
        printPeriodTempStats(records, &period);
        for (uint8_t month = January; month <= December; ++month) {
            period.month = month;
            printPeriodTempStats(records, &period);
        }
        printf("\n");
    }
}
