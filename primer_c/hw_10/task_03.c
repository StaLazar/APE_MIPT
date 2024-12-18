#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//! Вместимость строки, хранящейся в файле.
#define FILE_LINE_CAPACITY 1100

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
 * @brief Сдвинуть строку line, начиная с индекса pos, на shift символов влево.
 * @param line Строка, для которой будет применен сдвиг.
 * @param pos Индекс элемента, с которого будет начат сдвиг.
 * @param shift Величина сдвига.
 * @return true - операция сдвига прошла успешно, false - иначе.
 */
bool moveFileLineLeft(char line[FILE_LINE_CAPACITY], const size_t pos, const size_t shift) {
    if (pos >= FILE_LINE_CAPACITY) {
        printf("moveFileLineLeft: Invalid initial position\n");
        return false;
    }
    if (shift == 0) {
        return true;
    }
    const size_t begin = pos - shift;
    if (begin < 0) {
        printf("moveFileLineLeft: Unacceptable line shift\n");
        return false;
    }

    for (size_t i = begin; i <= strlen(line) - shift; ++i) {
        line[i] = line[i + shift];
    }
    for (size_t i = strlen(line) + 1UL - shift; i <= strlen(line); ++i) {
        line[i] = 0;
    }
    return true;
}

/**
 * @brief Сдвинуть строку line, начиная с индекса pos, на shift символов вправо.
 * @param line Строка, для которой будет применен сдвиг.
 * @param pos Индекс элемента, с которого будет начат сдвиг.
 * @param shift Величина сдвига.
 * @return true - операция сдвига прошла успешно, false - иначе.
 */
bool moveFileLineRight(char line[FILE_LINE_CAPACITY], const size_t pos, const size_t shift) {
    if (pos >= FILE_LINE_CAPACITY) {
        printf("moveFileLineRight: Invalid initial position\n");
        return false;
    }
    if (shift == 0) {
        return true;
    }
    const size_t end = strlen(line) + shift;
    if (end >= FILE_LINE_CAPACITY) {
        printf("moveFileLineRight: Unacceptable line shift\n");
        return false;
    }

    for (size_t i = end; i >= pos + shift; --i) {
        line[i] = line[i - shift];
    }
    for (size_t i = pos + shift - 1UL; i >= pos; --i) {
        line[i] = 0;
    }
    return true;
}

/**
 * @brief Заменить в строке line все вхождения подстроки rep на подстроку sub.
 * @param line Строка, в которой будет произведена замена.
 * @param rep Заменяемая подстрока.
 * @param sub Заменяющая подстрока.
 * @return true - замена прошла успешно, false - иначе.
 */
bool replaceFileLine(char line[FILE_LINE_CAPACITY], const char *rep, const char *sub) {
    for (char *ptr = strstr(line, rep); ptr; ptr = strstr(line, rep)) {
        const size_t repBegin = ptr - line;
        const size_t repEnd = repBegin + strlen(rep);
        const int difference = strlen(rep) - strlen(sub);
        if (difference < 0) {
            if (!moveFileLineRight(line, repEnd, abs(difference))) {
                return false;
            };
        } else if (difference > 0) {
            if (!moveFileLineLeft(line, repEnd, abs(difference))) {
                return false;
            };
        }
        for (size_t i = repBegin, j = 0; j < strlen(sub); ++i, ++j) {
            line[i] = *(sub + j);
        }
    }
    return true;
}

int main(void) {
    const char *inputPath = "input.txt";
    char fileLine[FILE_LINE_CAPACITY];
    memset(fileLine, 0, FILE_LINE_CAPACITY);
    if (!readFileLine(inputPath, fileLine)) {
        return 1;
    }

    const char *outputPath = "output.txt";
    const char *replaceable = "Cao";
    const char *substitute = "Ling";
    if (!replaceFileLine(fileLine, replaceable, substitute)) {
        return 2;
    };

    if (!writeFileLine(outputPath, fileLine)) {
        return 3;
    };

    return 0;
}
