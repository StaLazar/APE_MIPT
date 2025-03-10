#include "algorithm.h"
#include "common.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/**
 * @brief Вывести в консоль справку по приложению.
 * @details Справка по приложению представляет собой
 * описание функционала программы, а также список ключей,
 * их назначение и примеры использования.
 */
void printCmdHelp() {
    printf("General information\n");
    printf("  The application is designed to calculate the square of a figure\n");
    printf("  formed by a series of curved lines.\n\n");

    printf("Usage\n");
    printf("  calcularea -h\n");
    printf("  calcularea -a <float>\n");
    printf("  calcularea -s <float>\n");
    printf("  calcularea -r\n");
    printf("  calcularea -i\n");
    printf("  calcularea -l\n\n");

    printf("Options\n");
    printf("  -h\t\t = Print help information and exit.\n");
    printf("  -a <float>\t = Specify the precision of roots' calculation (0.001 by default).\n");
    printf("  -s <float>\t = Specify the precision of square's calculation (0.001 by default).\n");
    printf("  -r\t\t = Run test of roots' calculation (disabled by default).\n");
    printf("  -i\t\t = Run test of integral's calculation (disabled by default).\n");
    printf("  -l\t\t = Print abscissas of all intersection points (disabled by default).\n\n");
}

/**
 * @brief Основная функция приложения расчета площади фигуры.
 * @param[in] argc Количество переданных аргументов командной строки.
 * @param[in] argv Массив строк, представляющий переданный набор аргументов.
 * @retval 0 Приложение завершило работу в штатном режиме.
 * @retval 1 Приложение завершило работу с ошибкой при работе с аргументами командной строки.
 */
int main(int argc, char *argv[]) {
    float rootPrecision = 0.001F;
    float squarePrecision = 0.001F;
    bool isRootTestMode = false;
    bool isIntegralTestMode = false;
    bool isLogMode = false;

    opterr = 0;
    int option = 0;
    while ((option = getopt(argc, argv, "ha:s:ril")) != -1) {
        switch (option) {
            case 'h':
                printCmdHelp();
                return 0;
            case 'a':
                rootPrecision = (float) atof(optarg);
                break;
            case 's':
                squarePrecision = (float) atof(optarg);
                break;
            case 'r':
                isRootTestMode = true;
                break;
            case 'i':
                isIntegralTestMode = true;
                break;
            case 'l':
                isLogMode = true;
                break;
            case '?':
                printf("Unknown or invalid option '-%c'.\n", optopt);
                printf("Run 'calcularea -h' for all supported options.\n");
                return 1;
        }
    }

    roots[0] = getRoot(rootScopes[0], f, h, rootPrecision);
    roots[1] = getRoot(rootScopes[1], g, h, rootPrecision);
    roots[2] = getRoot(rootScopes[2], f, h, rootPrecision);
    roots[3] = getRoot(rootScopes[3], g, h, rootPrecision);
    roots[4] = getRoot(rootScopes[4], f, g, rootPrecision);

    const float_pair firstScope = {roots[0], roots[1]};
    const float_pair secondScope = {roots[1], roots[4]};
    float square = 0.F;
    square += getSquare(firstScope, f, h, squarePrecision);
    square += getSquare(secondScope, f, g, squarePrecision);

    if (isRootTestMode) {
        const float testRoot = 3.847760F;
        printf("Root test mode.\n");
        printf("Target: %f\tCalculated: %f\n\n", testRoot, roots[4]);
    }
    if (isIntegralTestMode) {
        const float testSquare = 40.324078F;
        printf("Integral test mode.\n");
        printf("Target: %f\tCalculated: %f\n\n", testSquare, square);
    }
    if (isLogMode) {
        printf("Abscissas of all intersection points:\n");
        for (size_t i = 0UL; i < ROOTS_COUNT; ++i) {
            printf("%f\t", roots[i]);
        }
        printf("\n\n");
    }
    printf("The square of the desired figure: %f\n", square);

    return 0;
}
