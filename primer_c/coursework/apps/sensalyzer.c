#include "timestamp.h"
#include "vector.h"
#include "temperature.h"
#include "cmd_handler.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Макрос освобождения памяти.
 * @param[out] ptr Указатель на объект, из-под которого нужно высвободить память.
 */
#define FREE_MEMORY(ptr) \
    if ((ptr) != NULL) { \
        free((ptr)); \
        (ptr) = NULL; \
    }

/**
 * @ingroup apps
 * @brief Основная функция приложения Sensalyzer.
 * @param[in] argc Количество переданных аргументов командной строки.
 * @param[in] argv Массив строк, представляющий переданный набор аргументов.
 * @retval 0 Приложение завершило работу в штатном режиме.
 * @retval 1 Приложение завершило работу с ошибкой при работе со входным файлом.
 */
int main(int argc, char *argv[]) {
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

    printf("\n------------");
    printf(" Errors occurred during the file and CMD processing ");
    printf("------------\n\n");
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
    printf("\n--------------");
    printf(" Temperature statistics based on specified file ");
    printf("--------------\n\n");
    if (!isVoidTimestamp(&period)) {
        printPeriodTempStats(&records, &period);
        printf("\n");
    } else {
        printGlobalTempStats(&records);
    }

    clearVector(&records);
    FREE_MEMORY(filePath)
    FREE_MEMORY(timeDate)

    return 0;
}
