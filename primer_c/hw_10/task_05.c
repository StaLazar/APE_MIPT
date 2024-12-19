#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//! Вместимость строки, хранящейся в файле.
#define FILE_LINE_CAPACITY 30

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
 * @brief Получить символ, соответствующий переданной цифре.
 * @param digit Цифра, символьный эквивалент которой необходимо получить.
 * @return Символ, соответствующий переданной цифре.
 */
char getCharByDigit(const size_t digit) {
    static const char *chars = "0123456789";

    return (digit < strlen(chars)) ? chars[digit] : '0';
}

/**
 * @brief Записать в строку output полный Soundex-код строки input, начиная со второго символа.
 * @attention Строка input должна состоять из строчных латинских букв.
 * @param input Строка, по которой будет составлен Soundex-код.
 * @param output Строка, куда будет записан полученный Soundex-код.
 */
void encodeSdxAlpha(char input[FILE_LINE_CAPACITY], char output[FILE_LINE_CAPACITY]) {
    static const char *codeTable[] = {"", "bfpv", "cgjkqsxz", "dt", "l", "mn", "r"};
    static const size_t codeTableSize = sizeof(codeTable) / sizeof(char *);

    for (size_t inIdx = 1, outIdx = 1; (inIdx < strlen(input)) && (outIdx < FILE_LINE_CAPACITY); ++inIdx) {
        for (size_t typeIdx = 1; typeIdx < codeTableSize; ++typeIdx) {
            if (strchr(codeTable[typeIdx], input[inIdx])) {
                output[outIdx++] = getCharByDigit(typeIdx);
                break;
            }
        }
    }
}

/**
 * @brief Сократить в Soundex-строке все последовательности цифр до одной такой цифры.
 * @param line Строка, представляющая собой Soundex-код.
 */
void replaceSdxCopies(char line[FILE_LINE_CAPACITY]) {
    size_t resIdx = 0;
    for (size_t origIdx = 1; origIdx < strlen(line); ++origIdx) {
        if (line[origIdx] != line[resIdx]) {
            line[++resIdx] = line[origIdx];
        }
    }
    line[++resIdx] = '\0';
}

/**
 * @brief Привести полный Soundex-код к стандартной длине.
 * @param line Строка, представляющая собой полный Soundex-код.
 */
void trimSdxCode(char line[FILE_LINE_CAPACITY]) {
    static const size_t codeLength = 4UL;
    static const char filler = '0';

    if (strlen(line) == codeLength) {
        return;
    }
    if (strlen(line) > codeLength) {
        line[codeLength] = '\0';
        return;
    }
    for (size_t idx = strlen(line); idx < codeLength; ++idx) {
        line[idx] = filler;
    }
    line[codeLength] = '\0';
}

/**
 * @brief Сформировать Soundex-код строки.
 * @param input Строка, по которой будет сформирован Soundex-код.
 * @param output Строка, куда будет записан полученный Soundex-код.
 */
void generateSoundexCode(char input[FILE_LINE_CAPACITY], char output[FILE_LINE_CAPACITY]) {
    output[0] = input[0];
    encodeSdxAlpha(input, output);
    replaceSdxCopies(output);
    trimSdxCode(output);
}

int main(void) {
    const char *inputPath = "input.txt";
    char inputLine[FILE_LINE_CAPACITY];
    memset(inputLine, 0, FILE_LINE_CAPACITY);
    if (!readFileLine(inputPath, inputLine)) {
        return 1;
    }

    const char *outputPath = "output.txt";
    char outputLine[FILE_LINE_CAPACITY];
    memset(outputLine, 0, FILE_LINE_CAPACITY);
    generateSoundexCode(inputLine, outputLine);

    if (!writeFileLine(outputPath, outputLine)) {
        return 2;
    };

    return 0;
}
