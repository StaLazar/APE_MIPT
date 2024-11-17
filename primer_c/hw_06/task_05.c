#include <stdio.h>

/**
 * @brief Преобразовать символ-цифру в соответствующее число.
 * @param digit Символ-цифра.
 * @return Искомое число.
 */
int digitToNumber(const char digit) {
    switch (digit) {
        case '9':
            return 9;
        case '8':
            return 8;
        case '7':
            return 7;
        case '6':
            return 6;
        case '5':
            return 5;
        case '4':
            return 4;
        case '3':
            return 3;
        case '2':
            return 2;
        case '1':
            return 1;
        case '0':
        default:
            return 0;
    }
}

int main(void) {
    char symbol = '0';
    int sum = 0;

    printf("Input a row ending with '.':\n");

    const char finalSymbol = '.';
    for (scanf("%c", &symbol); symbol != finalSymbol; scanf("%c", &symbol)) {
        if (('0' <= symbol) && (symbol <= '9')) {
            sum += digitToNumber(symbol);
        }
    }

    printf("\nThe sum of digits in row: %d\n", sum);

    return 0;
}
