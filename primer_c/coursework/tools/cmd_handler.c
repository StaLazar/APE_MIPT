#include "cmd_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/**
 * @brief Скопировать содержимое строки source в строку destination.
 * @details В случае неудачного копирования в destination будет записан NULL.
 * @param[out] destination Строка, в которую будет произведено копирование.
 * @param[in] source Строка, из которой будет произведено копирование.
 */
static void copyString(char **destination, const char *source) {
    const size_t size = sizeof(char) * (strlen(source) + 1UL);
    *destination = (char *) malloc(size);
    if (*destination == NULL) {
        return;
    }
    memset(*destination, 0, size);
    strcpy(*destination, source);
}

void printCmdHelp() {
    printf("General information\n");
    printf("  Sensalyzer is an application for analyzing sensors' records.\n");
    printf("  It can read data files compiled in accordance with\n");
    printf("  the established protocol of information interaction and\n");
    printf("  display statistics on them for a specified time period.\n\n");

    printf("Usage\n");
    printf("  sensalyzer -h\n");
    printf("  sensalyzer -f <path-to-file>\n");
    printf("  sensalyzer -f <path-to-file> -t <year>[.<month>[.<day>[-<hour>[:<minute>]]]]\n\n");

    printf("Options\n");
    printf("  -h\t\t\t = Print help information and exit.\n");
    printf("  -f <path-to-file>\t = Specify the path to the sensor's data file.\n");
    printf("  -t <year>[.<month>[.<day>[-<hour>[:<minute>]]]]\n");
    printf("    \t\t\t = Explicitly specify the time period for statistics.\n\n");
}

void handleCmdCommands(int argc, char *argv[], bool *isHelpReceived, char **path, char **timeDate) {
    opterr = 0;
    int option = 0;
    while ((option = getopt(argc, argv, "hf:t:")) != -1) {
        switch (option) {
            case 'h':
                *isHelpReceived = true;
                printCmdHelp();
                break;
            case 'f':
                copyString(path, optarg);
                break;
            case 't':
                copyString(timeDate, optarg);
                break;
            case '?':
                printf("Unknown or invalid option '-%c'.\n", optopt);
                printf("Run 'sensalyzer -h' for all supported options.\n");
                break;
        }
    }
}
