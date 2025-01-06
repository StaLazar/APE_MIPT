#include "common/timestamp.h"
#include "common/vector.h"
#include "sensors/temperature.h"
#include "tools/cmd_interface.h"

#include <stdio.h>

void printTempData(const vector *records) {
    printf("\n--- temp_data ---\n");
    for (size_t i = 0U; i < getVectorSize(records); ++i) {
        const temp_data *data = (const temp_data *) getVectorElement(records, i);
        printf("%d.%d.%d-%d:%d\t---\t%+d\n", data->timestamp.year, data->timestamp.month,
                data->timestamp.day, data->timestamp.hour, data->timestamp.minute,
                data->record.value);
    }
    printf("--- temp_data ---\n\n");
}

void test() {
    printf("Hello world!\n");

    vector records;
    initVector(&records, sizeof(temp_data), 1U);

    timestamp tm1 = {2021U, 1U, 2U, 13U, 2U};
    timestamp tm2 = {2022U, 1U, 3U, 13U, 2U};
    timestamp tm3 = {2021U, 1U, 1U, 13U, 2U};
    timestamp tm4 = {2021U, 2U, 5U, 13U, 2U};

    temp_record re1 = makeTempRecord(50);
    temp_record re2 = makeTempRecord(20);
    temp_record re3 = makeTempRecord(10);
    temp_record re4 = makeTempRecord(30);

    temp_data td1 = {tm1, re1};
    temp_data td2 = {tm2, re2};
    temp_data td3 = {tm3, re3};
    temp_data td4 = {tm4, re4};

    addVectorElement(&records, &td1);
    addVectorElement(&records, &td2);
    addVectorElement(&records, &td3);
    addVectorElement(&records, &td4);

    printTempData(&records);
    qsortTempByTimestamp(&records);
    printTempData(&records);

    timestamp base;
    makeVoidTimestamp(&base);
    base.year = 2021U;
    base.month = 1U;

    printf("\nTemperature statistics for %d:\n", base.year);
    printTempStats(&records, &base);
    printf("\n");

    clearVector(&records);
}

int main () {
    test();

    return 0;
}
