#include "cmd_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void printCmdHelp() {
    printf("General information\n\n");
    printf("\tSensalyzer is an application for analyzing sensors' records.\n");
    printf("\tIt can read data files compiled in accordance with\n");
    printf("\tthe established protocol of information interaction and\n");
    printf("\tdisplay statistics on them for a specified time period.\n\n");

    printf("Usage\n\n");
    printf("\tsensalyzer -h\n");
    printf("\tsensalyzer -f <path-to-file>\n");
    printf("\tsensalyzer -f <path-to-file> -t <year>[.<month>[.<day>[-<hour>[:<minute>]]]]\n\n");

    printf("Options\n\n");
    printf("\t-h\t = Print help information and exit.\n");
    printf("\t-f <path-to-file>\t = Specify the path to the sensor's data file.\n");
    printf("\t-t <year>[.<month>[.<day>[-<hour>[:<minute>]]]]\t = ");
    printf("Explicitly specify the time period for statistics output.\n\n");
}

void handleCmdCommands(const int argc, char *argv[], char *path, char *timeDate) {
    opterr = 0;
    int option = 0;
    while ((option = getopt(argc, argv, "hf:t:")) != -1) {
        switch (option) {
            case 'h':
                printCmdHelp();
                break;
            case 'f':
                path = (char *) malloc(sizeof(char) * strlen(optarg));
                memcpy(path, optarg, sizeof(char) * strlen(optarg));
                break;
            case 't':
                timeDate = (char *) malloc(sizeof(char) * strlen(optarg));
                memcpy(timeDate, optarg, sizeof(char) * strlen(optarg));
                break;
            case '?':
                printf("Unknown or invalid option '-%c'.\n", optopt);
                printf("Run 'sensalyzer -h' for all supported options.\n");
                break;
        }
    }
}
