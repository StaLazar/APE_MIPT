#include "common/timestamp.h"
#include "common/vector.h"
#include "sensors/temperature.h"
#include "tools/cmd_handler.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Макрос освобождения памяти.
 * @param ptr Указатель на объект, из-под которого нужно высвободить память.
 */
#define FREE_MEMORY(ptr) \
    if ((ptr) != NULL) { \
        free((ptr)); \
        (ptr) = NULL; \
    }

void printTempData(const vector *records) {
    printf("\n--- temp_data ---\n");
    for (size_t i = 0U; i < getVectorSize(records); ++i) {
        const temp_data *data = (const temp_data *) getVectorElement(records, i);
        printTimestamp(&(data->timestamp));
        printf("\t---\t");
        printTempRecord(&(data->record));
        printf("\n");
    }
    printf("--- temp_data ---\n\n");
}

void testWork() {
    vector records;
    initVector(&records, sizeof(temp_data), 1UL);

    if (!readTempFromFile("debugging_data.csv", &records)) {
        clearVector(&records);
        return;
    }

    printTempData(&records);
    qsortTempByTimestamp(&records);
    printTempData(&records);

    timestamp base;
    makeVoidTimestamp(&base);
    base.year = 2022U;
    base.month = 1U;
    base.day = 16U;
    base.hour = 1U;

    printf("\nTemperature statistics for ");
    printTimestamp(&base);
    printf(" :\n");
    printTempStats(&records, &base);
    printf("\n");

    clearVector(&records);
}

void testTimestamp() {
    timestamp base;
    makeVoidTimestamp(&base);

    char *format = "2024.10.13-14:15";
    makeTimestamp(&base, format);

    printTimestamp(&base);
    printf("\n");
}

int main (int argc, char *argv[]) {
    if (argc == 1) {
        printCmdHelp();
        return 0;
    }

    bool isHelpReceived = false;
    char *filePath = NULL;
    char *timeDate = NULL;
    handleCmdCommands(argc, argv, &isHelpReceived, &filePath, &timeDate);
    if (isHelpReceived) {
        FREE_MEMORY(filePath)
        FREE_MEMORY(timeDate)
        return 0;
    }

    vector records;
    initVector(&records, sizeof(temp_data), 1UL);
    if (!readTempFromFile(filePath, &records)) {
        clearVector(&records);
        FREE_MEMORY(filePath)
        FREE_MEMORY(timeDate)
        return 1;
    }
    if (isVectorEmpty(&records)) {
        printf("There is no data in file '%s'\n", filePath);
        clearVector(&records);
        FREE_MEMORY(filePath)
        FREE_MEMORY(timeDate)
        return 1;
    }
    qsortTempByTimestamp(&records);

    timestamp period;
    makeTimestamp(&period, timeDate);
    printf("\nTemperature statistics based on data from '%s'\n", filePath);
    if (!isVoidTimestamp(&period)) {
        printTempStats(&records, &period);
    } else {
        //! TODO: Реализовать функцию вывода общей статистики по всему файлу.
    }

    clearVector(&records);
    FREE_MEMORY(filePath)
    FREE_MEMORY(timeDate)

    return 0;
}
