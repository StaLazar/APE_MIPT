#include "common/timestamp.h"
#include "common/vector.h"
#include "sensors/temperature.h"
#include "tools/cmd_handler.h"

#include <stdio.h>

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
    initVector(&records, sizeof(temp_data), 1U);

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

int main () {
    testTimestamp();
    // testWork();

    return 0;
}
