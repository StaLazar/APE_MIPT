#include <stdio.h>

int main(void) {
    char symbol = '0';
    char letterShift = 'a' - 'A';

    const char finalSymbol = '.';
    for (scanf("%c", &symbol); symbol != finalSymbol;) {
        if (('A' <= symbol) && (symbol <= 'Z')) {
            printf("%c", symbol + letterShift);
        } else {
            printf("%c", symbol);
        }
        scanf("%c", &symbol);
    }
    printf("\n");

    return 0;
}
