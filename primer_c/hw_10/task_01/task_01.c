#include <stdio.h>
#include <stdbool.h>

#define FILE_LINE_CAPACITY 1000

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

    if (fprintf(file, "%s", line) < 0) {
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
 * @brief Получить фактический размер строки, прочитанной из файла.
 * @param line Строка, размер которой будет определен.
 * @return Фактический размер строки, прочитанной из файла.
 */
size_t getFileLineSize(const char line[FILE_LINE_CAPACITY]) {
    size_t lineSize = 0;
    for (size_t i = 0; i < FILE_LINE_CAPACITY; ++i) {
        if (line[i] != 0) {
            ++lineSize;
        } else {
            break;
        }
    }
    return lineSize;
}

/**
 * @brief Определить, является ли строка, прочитанная из файла, палиндромом.
 * @details Палиндром - строка, которая читается одинаково в обоих направлениях.
 * @param line Строка для проверки.
 * @return true - строка является палиндромом, false - иначе.
 */
bool isPalindrome(const char line[FILE_LINE_CAPACITY]) {
    const size_t lineSize = getFileLineSize(line);
    for (size_t i = 0, j = lineSize - 1; i < j; ++i, --j) {
        if (line[i] != line[j]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    const char *inputPath = "input.txt";
    char inputLine[FILE_LINE_CAPACITY];
    if (!readFileLine(inputPath, inputLine)) {
        return 1;
    }

    const char *outputPath = "output.txt";
    const char *outputLine = isPalindrome(inputLine) ? "YES\n" : "NO\n";
    if (!writeFileLine(outputPath, outputLine)) {
        return 2;
    };

    return 0;
}
