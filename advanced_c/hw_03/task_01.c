#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//! Максимальный размер входной строки.
#define MAX_INPUT_SIZE 101UL
//! Количество трехзначных чисел.
#define THREE_DIGITS_COUNT 900UL

int main() {
    char input[MAX_INPUT_SIZE];
    memset(input, 0, sizeof(char) * MAX_INPUT_SIZE);
    bool numList[THREE_DIGITS_COUNT];
    memset(numList, 0, sizeof(bool) * THREE_DIGITS_COUNT);
    size_t uniqueCount = 0UL;

    printf("Input a natural number: ");
    scanf("%s", input);

    const size_t inputLength = strlen(input);
    if (inputLength < 3UL) {
        printf("Amount of unique three-digit numbers: %ld\n", uniqueCount);
        return 0;
    }
    for (size_t hundreds = 0UL; hundreds < inputLength - 2UL; ++hundreds) {
        if (input[hundreds] == '0') {
            continue;
        }
        for (size_t tens = hundreds + 1UL; tens < inputLength - 1UL; ++tens) {
            for (size_t ones = tens + 1UL; ones < inputLength; ++ones) {
                int number = (input[hundreds] - '0') * 100 +
                        (input[tens] - '0') * 10 + (input[ones] - '0');
                numList[number - 100] = true;
            }
        }
    }
    for (size_t i = 0UL; i < THREE_DIGITS_COUNT; ++i) {
        if (numList[i]) {
            ++uniqueCount;
        }
    }

    printf("Amount of unique three-digit numbers: %ld\n", uniqueCount);

    return 0;
}
