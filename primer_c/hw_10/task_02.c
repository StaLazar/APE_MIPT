#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//! Вместимость строки, хранящейся в файле.
#define FILE_LINE_CAPACITY 1000
//! Вместимость строки, хранящей расширение файла.
#define FILE_EXT_CAPACITY 10

//! Символ, выступающий в роли разделителя элементов путей.
#define DIR_SEPARATOR '/'
//! Символ, выступающий в роли разделителя расширений файла.
#define EXT_SEPARATOR '.'

/**
 * @brief Прочитать строку из файла.
 * @param path Путь к файлу для чтения.
 * @param line Строка, в которую будут записаны данные.
 * @return true - чтение прошло успешно, false - иначе.
 */
bool readFileLine(const char *path, char *line) {
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("readFileLine");
        return false;
    }

    if (fscanf(file, "%[^\n]", line) == EOF) {
        printf("readFileLine: No data to read\n");
        return false;
    } else if (ferror(file)) {
        perror("readFileLine");
        return false;
    }

    fclose(file);
    return true;
}

/**
 * @brief Записать строку в файл.
 * @param path Путь к файлу для записи.
 * @param line Строка, которая будет записана в файл.
 * @return true - запись прошла успешно, false - иначе.
 */
bool writeFileLine(const char *path, const char *line) {
    FILE *file = fopen(path, "w");
    if (!file) {
        perror("writeFileLine");
        return false;
    }

    if (fprintf(file, "%s\n", line) < 0) {
        printf("writeFileLine: Data recording error\n");
        return false;
    } else if (ferror(file)) {
        perror("writeFileLine");
        return false;
    }

    fclose(file);
    return true;
}

/**
 * @brief Сменить расширение файла.
 * @param line Путь до файла, которому нужно сменить расширение.
 * @param extension Новое расширение файла.
 * @return true - смена расширения прошла успешно, false - иначе.
 */
bool changeExtension(char line[FILE_LINE_CAPACITY], const char extension[FILE_EXT_CAPACITY]) {
    size_t extIdx = 0;
    for (size_t i = strlen(line) - 1; i >= 0; --i) {
        if (line[i] == EXT_SEPARATOR) {
            extIdx = i;
            break;
        }
        if (line[i] == DIR_SEPARATOR) {
            extIdx = strlen(line);
            break;
        }
    }
    if (extIdx >= FILE_LINE_CAPACITY) {
        printf("changeExtension: Index is out of range\n");
        return false;
    }

    for (size_t i = extIdx; i < strlen(line); ++i) {
        line[i] = 0;
    }

    size_t changeCount = 0;
    for (size_t i = extIdx, j = 0; (i < FILE_LINE_CAPACITY) && (j < FILE_EXT_CAPACITY); ++i, ++j) {
        line[i] = extension[j];
        ++changeCount;
    }
    if (changeCount != FILE_EXT_CAPACITY) {
        printf("changeExtension: Extension changing error\n");
        return false;
    }

    return true;
}

int main(void) {
    const char *inputPath = "input.txt";
    char fileLine[FILE_LINE_CAPACITY];
    if (!readFileLine(inputPath, fileLine)) {
        return 1;
    }

    const char *outputPath = "output.txt";
    const char extension[FILE_EXT_CAPACITY] = ".html";
    if (!changeExtension(fileLine, extension)) {
        return 2;
    }

    if (!writeFileLine(outputPath, fileLine)) {
        return 3;
    };

    return 0;
}
